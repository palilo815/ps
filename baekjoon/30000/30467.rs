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
    size: usize,
    tree: Box<[T]>,
}

impl<T> FenwickTree<T>
where
    T: Clone + Copy + Default + std::ops::AddAssign + std::ops::Sub<Output = T>,
{
    fn new(size: usize) -> Self {
        Self {
            size,
            tree: vec![T::default(); size + 1].into_boxed_slice(),
        }
    }
    fn update(&mut self, mut i: usize, x: T) {
        assert!(i <= self.size);
        i += 1;
        while i <= self.size {
            self.tree[i] += x;
            i += i & i.wrapping_neg();
        }
    }
    fn prefix(&self, mut i: usize) -> T {
        assert!(i <= self.size);
        let mut acc = T::default();
        while i != 0 {
            acc += self.tree[i];
            i &= i - 1;
        }
        acc
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let s = sc.read::<usize>();
    let mut a = sc.read_vec::<usize>(n);
    let mut values = a.clone();
    values.sort_unstable();
    values.dedup();
    for x in a.iter_mut() {
        *x = values.partition_point(|v| v < x);
    }
    let mut fw = FenwickTree::new(values.len());
    let mut res = 0;
    for &x in a.iter().take(s) {
        res += fw.prefix(x);
        fw.update(x, 1);
    }
    let mut ans = res;
    for i in s..n {
        res -= s - fw.prefix(a[i - s] + 1);
        fw.update(a[i - s], usize::MAX);
        res += fw.prefix(a[i]);
        fw.update(a[i], 1);
        ans = ans.max(res);
    }
    writeln!(out, "{ans}").ok();
}
