use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

struct FenwickTree<T> {
    pub size: usize,
    pub tree: Box<[T]>,
}

impl<T> FenwickTree<T>
where
    T: Clone + Copy + Default + std::ops::AddAssign,
{
    fn new(size: usize) -> Self {
        Self {
            size,
            tree: vec![T::default(); size + 1].into_boxed_slice(),
        }
    }
    fn add(&mut self, mut i: usize, x: T) {
        assert!(i <= self.size);
        i += 1;
        while i <= self.size {
            self.tree[i] += x;
            i += i & i.wrapping_neg();
        }
    }
    fn prefix_sum(&self, mut r: usize) -> T {
        assert!(r <= self.size);
        let mut sum = T::default();
        while r != 0 {
            sum += self.tree[r];
            r &= r - 1;
        }
        sum
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let mut a = sc.read_vec::<usize>(n);
    let mut compressed = a.clone();
    compressed.sort_unstable();
    for x in a.iter_mut() {
        *x = compressed.partition_point(|v| v < x);
    }
    const MOD: usize = 1_000_000_007;
    let mut fenwick = FenwickTree::new(n);
    let mut fac = 1;
    let mut ord = 1;
    for (i, x) in a.into_iter().rev().enumerate() {
        let smaller = fenwick.prefix_sum(x);
        fenwick.add(x, 1);
        ord = (ord + smaller * fac) % MOD;
        fac = (fac * (i + 1)) % MOD;
    }
    writeln!(out, "{ord}").ok();
}
