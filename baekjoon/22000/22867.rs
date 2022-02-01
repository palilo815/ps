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

trait ChMinMax {
    fn chmin(&mut self, x: Self) -> bool;
    fn chmax(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChMinMax for T {
    fn chmin(&mut self, x: Self) -> bool {
        *self > x && {
            *self = x;
            true
        }
    }
    fn chmax(&mut self, x: Self) -> bool {
        *self < x && {
            *self = x;
            true
        }
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let mut tin = vec![0; n];
    let mut tout = vec![0; n];
    for i in 0..n {
        let s = sc.next_bytes();
        let t = ((s[0] - b'0') as u32 * 60 * 60 * 1000 * 10)
            + ((s[1] - b'0') as u32 * 60 * 60 * 1000)
            + ((s[3] - b'0') as u32 * 60 * 1000 * 10)
            + ((s[4] - b'0') as u32 * 60 * 1000)
            + ((s[6] - b'0') as u32 * 1000 * 10)
            + ((s[7] - b'0') as u32 * 1000)
            + ((s[9] - b'0') as u32 * 100)
            + ((s[10] - b'0') as u32 * 10)
            + ((s[11] - b'0') as u32);
        tin[i] = t;
        let s = sc.next_bytes();
        let t = ((s[0] - b'0') as u32 * 60 * 60 * 1000 * 10)
            + ((s[1] - b'0') as u32 * 60 * 60 * 1000)
            + ((s[3] - b'0') as u32 * 60 * 1000 * 10)
            + ((s[4] - b'0') as u32 * 60 * 1000)
            + ((s[6] - b'0') as u32 * 1000 * 10)
            + ((s[7] - b'0') as u32 * 1000)
            + ((s[9] - b'0') as u32 * 100)
            + ((s[10] - b'0') as u32 * 10)
            + ((s[11] - b'0') as u32);
        tout[i] = t;
    }
    tin.sort_unstable();
    tout.sort_unstable();
    let mut bus = 0;
    let mut ans = 0;
    let mut i = 0;
    let mut j = 0;
    while i != n {
        if tin[i] < tout[j] {
            bus += 1;
            ans.chmax(bus);
            i += 1;
        } else {
            bus -= 1;
            j += 1;
        }
    }
    writeln!(out, "{}", ans).ok();
}
