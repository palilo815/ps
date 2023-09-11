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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

struct DisjointSet {
    p: Vec<i32>,
    s: Vec<u64>,
    g: Vec<u64>,
}

impl DisjointSet {
    fn new(s: Vec<u64>) -> Self {
        let n = s.len();
        Self {
            p: vec![-1; n],
            s,
            g: vec![0; n],
        }
    }
    fn find(&mut self, u: usize) -> usize {
        if self.p[u] < 0 {
            u
        } else {
            let rt = self.find(self.p[u] as usize);
            self.p[u] = rt as i32;
            rt
        }
    }
    fn unite(&mut self, u: usize, v: usize) -> u64 {
        let mut u = self.find(u);
        let mut v = self.find(v);
        if u != v {
            if self.p[u] > self.p[v] {
                std::mem::swap(&mut u, &mut v);
            }
            self.p[u] += self.p[v];
            self.p[v] = u as i32;
            self.g[u] += self.g[v] + self.s[u] * self.s[v];
            self.s[u] += self.s[v];
        }
        self.g[u]
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let q = sc.read::<usize>();
    let mut dsu = DisjointSet::new(sc.read_vec::<u64>(n));
    for _ in 0..q {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        writeln!(out, "{}", dsu.unite(u, v)).ok();
    }
}
