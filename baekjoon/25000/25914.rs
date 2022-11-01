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
    p: Box<[i32]>,
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
    fn size_of(&mut self, u: usize) -> i32 {
        let r = self.find(u);
        -self.p[r]
    }
}

trait ChMinMax {
    fn chmin(&mut self, x: Self) -> bool;
    fn chmax(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChMinMax for T {
    fn chmin(&mut self, x: Self) -> bool {
        *self > x && {
            *self = x;
            true
        }
    }
    fn chmax(&mut self, x: Self) -> bool {
        *self < x && {
            *self = x;
            true
        }
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    fn dfs(
        adj: &[Vec<usize>],
        disc: &mut [i32],
        bridges: &mut Vec<(usize, usize)>,
        u: usize,
        p: usize,
    ) -> i32 {
        static mut T: i32 = 0;
        let mut res = unsafe {
            T += 1;
            T
        };
        disc[u] = res;
        for &v in adj[u].iter().filter(|&&v| v != p) {
            if disc[v] == -1 {
                let lo = dfs(adj, disc, bridges, v, u);
                res.chmin(lo);
                if lo > disc[u] {
                    bridges.push((u, v));
                }
            } else {
                res.chmin(disc[v]);
            }
        }
        res
    }
    let mut disc = vec![-1; n];
    let mut bridges = vec![];
    for i in 0..n {
        if disc[i] == -1 {
            dfs(&adj, &mut disc, &mut bridges, i, usize::MAX);
        }
    }
    let mut dsu = DisjointSet::new(n);
    for (u, v) in bridges.into_iter() {
        dsu.unite(u, v);
    }
    let mut fish = vec![0; n];
    for _ in 0..k {
        fish[dsu.find(sc.read::<usize>() - 1)] += 1;
    }
    let mut xorsum = 0;
    for u in 0..n {
        if u == dsu.find(u) && fish[u] != 0 {
            xorsum ^= dsu.size_of(u) - fish[u];
        }
    }
    let first = sc.read::<i32>();
    writeln!(out, "{}", if xorsum == 0 { 1 - first } else { first }).ok();
}
