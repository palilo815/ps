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
    let p = sc.read::<usize>() - 1;
    let mut dp = sc.read_vec::<i32>(n);
    dp.iter_mut().for_each(|x| *x -= sc.read::<i32>());
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut topo = Vec::with_capacity(n);
    topo.push(p);
    for i in 0..n {
        let u = topo[i];
        for v in adj[u].clone() {
            let j = adj[v].iter().position(|&x| x == u).unwrap();
            adj[v].swap_remove(j);
        }
        topo.extend_from_slice(&adj[u]);
    }
    for u in topo.into_iter().rev() {
        dp[u] += adj[u].iter().map(|&v| dp[v]).sum::<i32>();
        dp[u] = 0.min(dp[u]);
    }
    writeln!(out, "{}", -dp[p]).ok();
}
