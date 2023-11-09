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
    let mut a = (0..n).map(|i| (i, sc.read::<u64>())).collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| l.1.cmp(&r.1).then(r.0.cmp(&l.0)));
    let mut bit = BinaryIndexedTree::new(n, 0, std::cmp::max);
    for (i, x) in a {
        let mx = bit.prefix(i);
        bit.update(i, mx + x);
    }
    writeln!(out, "{}", bit.prefix(n)).ok();
}
