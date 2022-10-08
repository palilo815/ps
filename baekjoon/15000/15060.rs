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

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

struct DisjointSet {
    par: Box<[i32]>,
    dist: Box<[u32]>,
}

impl DisjointSet {
    fn new(n: usize) -> Self {
        Self {
            par: vec![-1; n].into_boxed_slice(),
            dist: vec![u32::MAX; n].into_boxed_slice(),
        }
    }
    fn find(&self, mut u: usize) -> usize {
        while self.par[u] >= 0 {
            u = self.par[u] as usize;
        }
        u
    }
    fn unite(&mut self, mut u: usize, mut v: usize, w: u32) -> bool {
        u = self.find(u);
        v = self.find(v);
        if u == v {
            return false;
        }
        if self.par[u] > self.par[v] {
            std::mem::swap(&mut u, &mut v);
        }
        self.par[u] += self.par[v];
        self.par[v] = u as i32;
        self.dist[v] = w;
        true
    }
    fn query(&self, mut u: usize, mut v: usize) -> u32 {
        let mut ret = u32::MAX;
        while u != v {
            if self.dist[u] > self.dist[v] {
                std::mem::swap(&mut u, &mut v);
            }
            ret = self.dist[u];
            u = self.par[u] as usize;
        }
        ret
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut edges = (0..m)
        .map(|_| {
            (
                sc.read::<usize>() - 1,
                sc.read::<usize>() - 1,
                sc.read::<u32>(),
            )
        })
        .collect::<Vec<_>>();
    edges.sort_unstable_by(|l, r| l.2.cmp(&r.2));
    let mut table = std::collections::HashMap::new();
    for &(u, v, w) in edges.iter() {
        table.insert((u, v), w);
    }
    let mut dsu = DisjointSet::new(n);
    let mut mst = 0;
    for (u, v, w) in edges.into_iter() {
        if dsu.unite(u, v, w) {
            mst += w;
        }
    }
    let q = sc.read::<usize>();
    for _ in 0..q {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        let r = mst - dsu.query(u, v) + table.get(&(u, v)).unwrap();
        writeln!(out, "{}", r).ok();
    }
}
