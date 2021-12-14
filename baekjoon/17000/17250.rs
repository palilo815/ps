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

use std::io::Write;

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

pub struct DisjointSet {
    p: Vec<i32>,
}

impl DisjointSet {
    pub fn new(n: usize) -> DisjointSet {
        DisjointSet { p: vec![-1; n] }
    }
    pub fn find(&mut self, mut u: usize) -> usize {
        assert!(u < self.p.len());
        while self.p[u] >= 0 {
            if self.p[self.p[u] as usize] >= 0 {
                self.p[u] = self.p[self.p[u] as usize];
            }
            u = self.p[u] as usize;
        }
        u
    }
    pub fn unite(&mut self, u: usize, v: usize) -> bool {
        assert!(u < self.p.len() && v < self.p.len());
        let mut u = self.find(u);
        let mut v = self.find(v);
        if u == v {
            return false;
        }
        if self.p[u] > self.p[v] {
            std::mem::swap(&mut u, &mut v);
        }
        self.p[u] += self.p[v];
        self.p[v] = u as i32;
        true
    }
    pub fn same(&mut self, u: usize, v: usize) -> bool {
        assert!(u < self.p.len() && v < self.p.len());
        self.find(u) == self.find(v)
    }
    pub fn size(&mut self, u: usize) -> usize {
        assert!(u < self.p.len());
        let root = self.find(u);
        (-self.p[root]) as usize
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let mut dsu = DisjointSet::new(n);
    for i in 0..n {
        dsu.p[i] = -sc.next::<i32>();
    }
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        dsu.unite(u, v);
        writeln!(out, "{}", dsu.size(u)).ok();
    }
}
