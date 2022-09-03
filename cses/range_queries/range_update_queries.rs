use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

pub struct BinaryIndexedTree<T> {
    size: usize,
    tree: Vec<T>,
    id: T,
}

impl<T> BinaryIndexedTree<T>
where
    T: std::clone::Clone
        + std::cmp::PartialOrd
        + std::marker::Copy
        + std::ops::AddAssign
        + std::ops::SubAssign
        + std::ops::Sub<Output = T>,
{
    pub fn new(size: usize, id: T) -> Self {
        Self {
            size,
            tree: vec![id; size + 1],
            id,
        }
    }
    pub fn build(&mut self) {
        for i in 1..self.size {
            let val = self.tree[i];
            let idx = i + (i & i.wrapping_neg());
            if idx <= self.size {
                self.tree[idx] += val;
            }
        }
    }
    pub fn fake_update(&mut self, i: usize, x: T) {
        if i < self.size {
            self.tree[i + 1] += x;
        }
    }
    pub fn update(&mut self, mut i: usize, x: T) {
        assert!(i <= self.size);
        i += 1;
        while i <= self.size {
            self.tree[i] += x;
            i += i & i.wrapping_neg();
        }
    }
    pub fn prefix(&self, mut i: usize) -> T {
        assert!(i <= self.size);
        let mut ret = self.id;
        while i != 0 {
            ret += self.tree[i];
            i &= i - 1;
        }
        ret
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let q = sc.read::<usize>();
    let mut bit = BinaryIndexedTree::new(n, 0);
    let mut prev = 0;
    for i in 0..n {
        let x = sc.read::<i64>();
        bit.fake_update(i, x - prev);
        prev = x;
    }
    bit.build();
    for _ in 0..q {
        match sc.read() {
            1 => {
                let l = sc.read::<usize>() - 1;
                let r = sc.read::<usize>();
                let x = sc.read::<i64>();
                bit.update(l, x);
                bit.update(r, -x);
            }
            _ => writeln!(out, "{}", bit.prefix(sc.read::<usize>())).unwrap(),
        }
    }
}
