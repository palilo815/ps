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

struct DisjointSet {
    pub p: Vec<i32>,
}

impl DisjointSet {
    fn new(n: usize) -> Self {
        Self { p: vec![-1; n] }
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
    const MAX: usize = 500_000;
    let mut check = [false; MAX + 2];
    let n = sc.read::<usize>();
    let mut dsu = DisjointSet::new(MAX + 1);
    let mut ans = 0;
    for _ in 0..n {
        let s = sc.read::<usize>();
        if !std::mem::replace(&mut check[s], true) {
            ans += 1;
            if check[s - 1] {
                if dsu.size_of(s - 1) & 1 == 1 {
                    ans -= 1;
                }
                dsu.unite(s - 1, s);
            }
            if check[s + 1] {
                if dsu.size_of(s) & 1 == 1 && dsu.size_of(s + 1) & 1 == 1 {
                    ans -= 1;
                }
                dsu.unite(s, s + 1);
            }
        }
        write!(out, "{ans} ").ok();
    }
}
