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

struct BinaryIndexedTree<T> {
    t: Box<[T]>,
}

impl<T> BinaryIndexedTree<T>
where
    T: std::default::Default + std::marker::Copy + std::ops::AddAssign,
{
    fn new(size: usize) -> Self {
        Self {
            t: vec![T::default(); size + 1].into_boxed_slice(),
        }
    }
    fn update(&mut self, mut i: usize, x: T) {
        i += 1;
        while i < self.t.len() {
            self.t[i] += x;
            i += i & i.wrapping_neg();
        }
    }
    fn prefix(&self, mut i: usize) -> T {
        let mut ret = T::default();
        while i != 0 {
            ret += self.t[i];
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
    let mut idx = vec![0; n];
    for i in 0..n {
        idx[sc.read::<usize>()] = i;
    }
    let mut bit = BinaryIndexedTree::new(n);
    let mut ans = 0;
    for i in 0..n {
        let pos = idx[sc.read::<usize>()];
        let small_lhs = bit.prefix(pos) as usize;
        let large_rhs = small_lhs + n - i - 1 - pos;
        bit.update(pos, 1);
        ans += small_lhs * large_rhs;
    }
    if ans == 0 {
        writeln!(out, "Attention is what I want").ok();
    } else {
        writeln!(out, "My heart has gone to paradise").ok();
        writeln!(out, "{ans}").ok();
    }
}
