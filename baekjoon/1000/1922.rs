use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

struct DisjointSet {
    p: Box<[i32]>,
}

impl DisjointSet {
    fn new(n: usize) -> Self {
        Self { p: vec![-1; n].into() }
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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u32>()))
        .collect::<Vec<_>>();
    edges.sort_unstable_by(|l, r| l.2.cmp(&r.2));
    let mut dsu = DisjointSet::new(n);
    let mut ans = 0;
    for (u, v, w) in edges {
        if dsu.unite(u, v) {
            ans += w;
        }
    }
    writeln!(bw, "{ans}").ok();
}
