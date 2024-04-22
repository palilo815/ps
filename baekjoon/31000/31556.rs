use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

struct Csr<T> {
    values: Box<[(usize, T)]>,
    pref: Box<[usize]>,
}

impl<T> std::ops::Index<usize> for Csr<T> {
    type Output = [(usize, T)];
    fn index(&self, i: usize) -> &Self::Output {
        &self.values[self.pref[i]..self.pref[i + 1]]
    }
}

impl<T: Copy + Default> Csr<T> {
    fn from_undirected_edges(n: usize, edges: Vec<(usize, usize, T)>) -> Self {
        let mut values = vec![(0, T::default()); edges.len() * 2].into_boxed_slice();
        let mut pref = vec![0; n + 1].into_boxed_slice();
        for &(u, v, _) in edges.iter() {
            pref[u] += 1;
            pref[v] += 1;
        }
        for i in 0..n {
            pref[i + 1] += pref[i];
        }
        for (u, v, w) in edges {
            pref[u] -= 1;
            values[pref[u]] = (v, w);
            pref[v] -= 1;
            values[pref[v]] = (u, w);
        }
        Self { values, pref }
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let p = (0..n).map(|_| sc.read::<usize>() - 1).collect::<Vec<_>>();
    let edges = (1..n).map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, ())).collect::<Vec<_>>();
    let csr = Csr::from_undirected_edges(n, edges);
    let num_leaf = (1..n).filter(|&i| csr[i].len() == 1).count();
    let mut pass = vec![0; n];
    for p in p.into_iter().take(num_leaf) {
        pass[p] += 1;
    }
    let mut topo = Vec::with_capacity(n);
    topo.push(0);
    let mut par = vec![usize::MAX; n];
    par[0] = 0;
    for i in 0..n {
        let u = topo[i];
        for &(v, _) in csr[u].iter() {
            if par[v] == usize::MAX {
                par[v] = u;
                topo.push(v);
            }
        }
    }
    let mut dp = vec![0; n];
    for u in topo.into_iter().skip(1).rev() {
        dp[u] += (csr[u].len() == 1) as i32;
        let done = dp[u].min(pass[u]);
        dp[par[u]] += dp[u] - done;
    }
    dp[0] -= dp[0].min(pass[0]);
    writeln!(bw, "{}", num_leaf as i32 - dp[0]).ok();
}
