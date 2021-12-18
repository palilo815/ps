use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a String) -> Scanner<'a> {
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

pub trait Monoid: std::clone::Clone + std::marker::Copy {
    fn id() -> Self;
    fn op(lhs: &Self, rhs: &Self) -> Self;
    fn rev_op(lhs: &Self, rhs: &Self) -> Self;
}

#[allow(dead_code)]
mod binary_indexed_tree {
    use crate::Monoid;
    pub struct BinaryIndexedTree<T: Monoid> {
        n: usize,
        tree: Vec<T>,
    }
    impl<T: Monoid> BinaryIndexedTree<T> {
        pub fn new(n: usize) -> Self {
            Self {
                n,
                tree: vec![T::id(); n + 1],
            }
        }
        pub fn build_with(data: Vec<T>) -> Self {
            let n = data.len();
            let mut a = vec![T::id(); n + 1];
            a[1..].copy_from_slice(&data);
            for i in 1..=n {
                let j = i + (i & i.wrapping_neg());
                if j <= n {
                    a[j] = T::op(&a[i], &a[j]);
                }
            }
            Self { n, tree: a }
        }
        pub fn get(&self, i: usize) -> T {
            assert!(i < self.n);
            if i & 1 == 0 {
                self.product(i, i + 1)
            } else {
                self.tree[i + 1]
            }
        }
        pub fn update(&mut self, mut i: usize, x: T) {
            assert!(i <= self.n);
            i += 1;
            while i <= self.n {
                self.tree[i] = T::op(&self.tree[i], &x);
                i += i & i.wrapping_neg();
            }
        }
        pub fn prefix(&self, mut i: usize) -> T {
            assert!(i <= self.n);
            let mut ret = T::id();
            while i != 0 {
                ret = T::op(&ret, &self.tree[i]);
                i &= i - 1;
            }
            ret
        }
        pub fn product(&self, l: usize, r: usize) -> T {
            assert!(l <= r);
            T::rev_op(&self.prefix(l), &self.prefix(r))
        }
        pub fn clear(&mut self) {
            self.tree.fill(T::id());
        }
    }
}

// TODO
impl Monoid for i64 {
    fn id() -> Self {
        0
    }
    fn op(lhs: &Self, rhs: &Self) -> Self {
        lhs + rhs
    }
    fn rev_op(lhs: &Self, rhs: &Self) -> Self {
        rhs - lhs
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

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let mut sectors = vec![vec![]; n];
    for i in 0..m {
        sectors[sc.next::<usize>() - 1].push(i);
    }
    let req = sc.next_vec::<i64>(n);
    let q = sc.next::<usize>();
    let meteors = (0..q)
        .map(|_| (sc.next::<usize>() - 1, sc.next::<usize>(), sc.next::<i64>()))
        .collect::<Vec<_>>();
    let mut intervals = vec![(0, q); n];
    let mut bit = binary_indexed_tree::BinaryIndexedTree::<i64>::new(m);
    loop {
        let mut queries = vec![vec![]; q];
        let mut done = true;
        for (i, &(lo, hi)) in intervals.iter().enumerate() {
            if lo != hi {
                queries[(lo + hi) >> 1].push(i);
                done = false;
            }
        }
        if done {
            break;
        }
        bit.clear();
        for (i, &(l, r, w)) in meteors.iter().enumerate() {
            if l < r {
                bit.update(l, w);
                bit.update(r, -w);
            } else {
                bit.update(0, w);
                bit.update(r, -w);
                bit.update(l, w);
            }
            for &state in queries[i].iter() {
                let mut gather = 0;
                for &x in sectors[state].iter() {
                    gather += bit.prefix(x + 1);
                    if gather >= req[state] {
                        break;
                    }
                }
                if gather < req[state] {
                    intervals[state].0 = i + 1;
                } else {
                    intervals[state].1 = i;
                }
            }
        }
    }
    for &(lo, _) in intervals.iter() {
        if lo == q {
            writeln!(out, "NIE").ok();
        } else {
            writeln!(out, "{}", lo + 1).ok();
        }
    }
}
