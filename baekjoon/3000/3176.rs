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

struct DisjointSet<T, F> {
    p: Box<[i32]>,
    value: Box<[T]>,
    f: F,
}

impl<T: Clone + Copy, F: Fn(&T, &T) -> bool> DisjointSet<T, F> {
    fn new(n: usize, e: T, f: F) -> Self {
        Self {
            p: vec![-1; n].into(),
            value: vec![e; n].into(),
            f,
        }
    }
    fn find(&self, mut u: usize) -> usize {
        while self.p[u] >= 0 {
            u = self.p[u] as usize;
        }
        u
    }
    fn unite(&mut self, u: usize, v: usize, w: T) {
        let mut u = self.find(u);
        let mut v = self.find(v);
        if self.p[u] > self.p[v] {
            std::mem::swap(&mut u, &mut v);
        }
        self.p[u] += self.p[v];
        self.p[v] = u as i32;
        self.value[v] = w;
    }
    fn query(&self, mut u: usize, mut v: usize) -> T {
        let mut res = self.value[u];
        while u != v {
            if (self.f)(&self.value[v], &self.value[u]) {
                std::mem::swap(&mut u, &mut v);
            }
            res = self.value[u];
            u = self.p[u] as usize;
        }
        res
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let mut edges = (1..n)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u32>()))
        .collect::<Vec<_>>();
    edges.sort_unstable_by(|l, r| l.2.cmp(&r.2));
    let mut dsu1 = DisjointSet::new(n, 0, u32::gt);
    let mut dsu2 = DisjointSet::new(n, u32::MAX, u32::lt);
    for &(u, v, w) in edges.iter().rev() {
        dsu1.unite(u, v, w);
    }
    for (u, v, w) in edges {
        dsu2.unite(u, v, w);
    }
    let q = sc.read::<usize>();
    for _ in 0..q {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        writeln!(out, "{} {}", dsu1.query(u, v), dsu2.query(u, v)).ok();
    }
}
