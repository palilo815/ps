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

struct Hld {
    par: Box<[usize]>,
    sub: Box<[usize]>,
    top: Box<[usize]>,
    tin: Box<[usize]>,
}

impl Hld {
    fn new(mut adj: Vec<Vec<usize>>) -> Self {
        let n = adj.len();
        let mut topo = Vec::with_capacity(n);
        topo.push(0);
        let mut par = vec![usize::MAX; n].into_boxed_slice();
        for i in 0..n {
            let u = topo[i];
            if let Some(p) = adj[u].iter().position(|&v| v == par[u]) {
                adj[u].swap_remove(p);
            }
            topo.extend_from_slice(&adj[u]);
            adj[u].iter().for_each(|&v| par[v] = u);
        }
        let mut sub = vec![1; n].into_boxed_slice();
        topo.iter().skip(1).rev().for_each(|&u| sub[par[u]] += sub[u]);
        let mut top = vec![0; n].into_boxed_slice();
        for i in 0..n {
            let u = topo[i];
            if let Some(&heavy) = adj[u].iter().max_by_key(|&&v| sub[v]) {
                top[heavy] = top[u];
                topo[i + 1] = heavy;
                adj[u].iter().filter(|&&v| v != heavy).fold(sub[heavy] + 1, |acc, &v| {
                    top[v] = v;
                    topo[i + acc] = v;
                    acc + sub[v]
                });
            }
        }
        let mut tin = vec![0; n].into_boxed_slice();
        topo.into_iter().enumerate().for_each(|(i, u)| tin[u] = i);
        Self { par, tin, top, sub }
    }
    fn get_lca(&self, mut u: usize, mut v: usize) -> usize {
        while self.top[u] != self.top[v] {
            if self.sub[self.top[u]] < self.sub[self.top[v]] {
                u = self.par[self.top[u]];
            } else {
                v = self.par[self.top[v]];
            }
        }
        std::cmp::min_by_key(u, v, |&i| self.tin[i])
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let hld = Hld::new(adj);
    let m = sc.read::<usize>();
    for _ in 0..m {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        writeln!(bw, "{}", hld.get_lca(u, v) + 1).ok();
    }
}
