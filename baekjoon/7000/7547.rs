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
            let root = self.find(self.p[u] as usize);
            self.p[u] = root as i32;
            root
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
    fn clear(&mut self, n: usize) {
        self.p[..n].fill(-1);
    }
    fn same(&mut self, u: usize, v: usize) -> bool {
        self.find(u) == self.find(v)
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let mut dsu = DisjointSet::new(1000);
    let t = sc.read::<usize>();
    for t in 1..=t {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        let mut edges = (0..m)
            .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u32>()))
            .collect::<Vec<_>>();
        edges.sort_unstable_by_key(|x| x.2);
        dsu.clear(n);
        for (u, v, w) in edges.into_iter().rev() {
            dsu.unite(u, v);
            if dsu.same(0, n - 1) {
                writeln!(bw, "Scenario #{t}:\n{w}\n").ok();
                break;
            }
        }
    }
}
