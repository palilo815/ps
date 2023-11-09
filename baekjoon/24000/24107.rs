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

struct BinaryIndexedTree<T, F> {
    size: usize,
    tree: Box<[T]>,
    e: T,
    f: F,
}

impl<T, F> BinaryIndexedTree<T, F>
where
    T: Clone + Copy,
    F: Fn(T, T) -> T,
{
    fn new(size: usize, e: T, f: F) -> Self {
        Self {
            size,
            tree: vec![e; size + 1].into(),
            e,
            f,
        }
    }
    fn update(&mut self, mut i: usize, x: T) {
        assert!(i <= self.size);
        i += 1;
        while i <= self.size {
            self.tree[i] = (self.f)(self.tree[i], x);
            i += i & i.wrapping_neg();
        }
    }
    fn prefix(&self, mut i: usize) -> T {
        assert!(i <= self.size);
        let mut ret = self.e;
        while i != 0 {
            ret = (self.f)(ret, self.tree[i]);
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
    let w = sc.read_vec::<u64>(n);
    let mut bit = BinaryIndexedTree::new(n, 0, std::cmp::max);
    for _ in 0..n {
        let i = sc.read::<usize>() - 1;
        let lis = w[i] + bit.prefix(i); // not longest, it's largest
        bit.update(i, lis);
    }
    let ans = 2 * (w.into_iter().sum::<u64>() - bit.prefix(n));
    writeln!(out, "{ans}").ok();
}
