use std::io::*;

struct Scanner {
    it: std::str::SplitWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut out = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut w = sc.read_vec::<i32>(n);
    let total = w.iter().sum::<i32>();
    let mut par = vec![usize::MAX; n];
    par[0] = 0;
    let mut topo = Vec::with_capacity(n);
    topo.push(0);
    for i in 0..n {
        let u = topo[i];
        for v in std::mem::take(&mut adj[u]) {
            if par[v] == usize::MAX {
                par[v] = u;
                topo.push(v);
            }
        }
    }
    let mut best = (u32::MAX, 0, 0);
    for u in topo.into_iter().rev() {
        w[par[u]] += w[u];
        let diff = w[u].abs_diff(total - w[u]);
        if diff < best.0 {
            best = (diff, u, par[u]);
        }
    }
    writeln!(out, "{}\n{} {}", best.0, best.1 + 1, best.2 + 1).ok();
}
