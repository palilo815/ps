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
    p: Vec<i32>,
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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<i64>()))
        .collect::<Vec<_>>();
    edges.sort_unstable_by(|l, r| r.2.cmp(&l.2));
    let mut dsu = DisjointSet::new(n);
    let mut adj = vec![vec![]; n];
    let mut mst = 0;
    for (u, v, w) in edges.into_iter() {
        if dsu.unite(u, v) {
            adj[u].push((w, v));
            adj[v].push((w, u));
            mst += w;
        }
    }
    let root = sc.read::<usize>() - 1;
    let mut dist = vec![-1; n];
    dist[root] = 0;
    let mut stack = Vec::with_capacity(n);
    stack.push(root);
    while let Some(u) = stack.pop() {
        for &(w, v) in adj[u].iter() {
            if dist[v] == -1 {
                dist[v] = dist[u] + w;
                stack.push(v);
            }
        }
    }
    dist[root] = -1;
    let best_leaf = dist
        .into_iter()
        .zip(adj.into_iter().map(|x| x.len()))
        .filter(|x| x.1 == 1)
        .max_by(|l, r| l.0.cmp(&r.0))
        .unwrap()
        .0;
    writeln!(out, "{}", 2 * mst - best_leaf).ok();
}
