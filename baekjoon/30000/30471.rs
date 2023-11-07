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

struct DisjointSet {
    pub p: Box<[i32]>,
}

impl DisjointSet {
    fn new(n: usize) -> Self {
        Self {
            p: vec![-1; n].into_boxed_slice(),
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
    fn unite(&mut self, u: usize, v: usize) -> bool {
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
    fn same(&mut self, u: usize, v: usize) -> bool {
        self.find(u) == self.find(v)
    }
    fn size_of(&mut self, u: usize) -> usize {
        let root = self.find(u);
        (-self.p[root]) as usize
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut dsu = DisjointSet::new(n);
    let f = |x: usize| x * (x - 1) / 2;
    let mut ans = n;
    for _ in 0..m {
        let a = sc.read::<usize>() - 1;
        let b = sc.read::<usize>() - 1;
        if !dsu.same(a, b) {
            ans -= f(dsu.size_of(a));
            ans -= f(dsu.size_of(b));
            dsu.unite(a, b);
            ans += f(dsu.size_of(a));
        }
        writeln!(out, "{ans}").ok();
    }
}
