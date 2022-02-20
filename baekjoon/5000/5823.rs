use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

const SQ: usize = 400;

static mut L: i32 = 0;

struct B {
    pub pos: Vec<i32>,
    pub nxt: Vec<i32>,
    pub dp: Vec<i32>,
}

impl B {
    fn new(a: &[i32]) -> Self {
        let mut block = Self {
            pos: a.to_vec(),
            nxt: vec![0; a.len()],
            dp: vec![0; a.len()],
        };
        block.calc();
        block
    }
    fn insert(&mut self, x: i32) {
        let i = self.pos.partition_point(|&p| p < x);
        self.pos.insert(i, x);
        self.calc();
    }
    fn remove(&mut self, x: i32) {
        let i = self.pos.partition_point(|&p| p < x);
        self.pos.remove(i);
        self.calc();
    }
    fn split(&mut self) -> Self {
        let rhs = Self::new(&self.pos[SQ..]);
        self.pos.resize(SQ, 0);
        self.calc();
        rhs
    }
    fn calc(&mut self) {
        let n = self.pos.len();
        self.nxt.resize(n, 0);
        self.dp.resize(n, 0);
        let mut far = n;
        for i in (0..n).rev() {
            unsafe {
                while self.pos[i] + L < self.pos[far - 1] {
                    far -= 1;
                }
                if far == n {
                    self.nxt[i] = self.pos[i] + L;
                    self.dp[i] = 1;
                } else {
                    self.nxt[i] = self.nxt[far];
                    self.dp[i] = self.dp[far] + 1;
                }
            }
        }
    }
    fn len(&self) -> usize {
        self.pos.len()
    }
}

struct Blocks {
    blocks: Vec<B>,
}

impl Blocks {
    fn new(mut a: Vec<i32>) -> Self {
        a.sort_unstable();
        Self {
            blocks: a.chunks(SQ).map(B::new).collect(),
        }
    }
    fn insert(&mut self, x: i32) {
        let mut i = self.blocks.partition_point(|b| *b.pos.last().unwrap() < x);
        if i == self.blocks.len() {
            i -= 1;
        }
        self.blocks[i].insert(x);
        if self.blocks[i].len() == (SQ << 1) {
            let new_block = self.blocks[i].split();
            self.blocks.insert(i + 1, new_block);
        }
    }
    fn remove(&mut self, x: i32) {
        let i = self.blocks.partition_point(|b| *b.pos.last().unwrap() < x);
        if self.blocks[i].len() == 1 {
            self.blocks.remove(i);
        } else {
            self.blocks[i].remove(x);
        }
    }
    fn answer(&self) -> i32 {
        self.blocks
            .iter()
            .fold((i32::MIN, 0), |(rmost, ans), b| {
                let i = b.pos.partition_point(|&p| p <= rmost);
                if i == b.len() {
                    (rmost, ans)
                } else {
                    (b.nxt[i], ans + b.dp[i])
                }
            })
            .1
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    unsafe {
        L = sc.next::<i32>();
    }
    let m = sc.next::<usize>();
    let mut a = sc.next_vec::<i32>(n);
    let mut blocks = Blocks::new(a.clone());
    for _ in 0..m {
        let i = sc.next::<usize>();
        let y = sc.next::<i32>();
        let x = std::mem::replace(&mut a[i], y);
        blocks.remove(x);
        blocks.insert(y);
        writeln!(out, "{}", blocks.answer()).ok();
    }
}
