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

pub struct BinaryIndexedTree<T> {
    size: usize,
    tree: Vec<T>,
    id: T,
}

impl<T> BinaryIndexedTree<T>
where
    T: std::clone::Clone + std::marker::Copy + std::ops::AddAssign,
{
    pub fn new(size: usize, id: T) -> Self {
        Self {
            size,
            tree: vec![id; size + 1],
            id,
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

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let l = sc.read::<usize>();
    let mut inv = 0;
    let mut bit = BinaryIndexedTree::new(n, 0);
    for _ in 0..n {
        let i = n - sc.read::<usize>();
        inv += bit.prefix(i) as usize;
        bit.update(i, 1);
    }
    writeln!(out, "{}", (n * (n - 1) / 2).min(inv + l)).ok();
}
