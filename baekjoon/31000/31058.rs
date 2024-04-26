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
    fn from_direct_edges(n: usize, edges: Vec<(usize, usize, T)>) -> Self {
        let mut values = vec![(0, T::default()); edges.len()].into_boxed_slice();
        let mut pref = vec![0; n + 1].into_boxed_slice();
        for &(u, _, _) in edges.iter() {
            pref[u] += 1;
        }
        for i in 0..n {
            pref[i + 1] += pref[i];
        }
        for (u, v, w) in edges {
            pref[u] -= 1;
            values[pref[u]] = (v, w);
        }
        Self { values, pref }
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let rev_edges = (0..m)
        .map(|_| {
            let u = sc.read::<usize>() - 1;
            let v = sc.read::<usize>() - 1;
            (v, u, sc.read::<usize>())
        })
        .collect::<Vec<_>>();
    let mut indeg = vec![0; n];
    for &(_, v, _) in rev_edges.iter() {
        indeg[v] += 1;
    }
    let csr = Csr::from_direct_edges(n, rev_edges);
    let mut rev_topo = (0..n).filter(|&i| indeg[i] == 0).collect::<Vec<_>>();
    // len, sum, rank
    let mut dp = vec![(0, 0, 0); n];
    let mut prev_dist = 0;
    for i in 0..n {
        if dp[rev_topo[i]].0 != prev_dist {
            prev_dist += 1;
            rev_topo[i..].sort_unstable_by(|&l, &r| dp[l].2.cmp(&dp[r].2));
            for (i, &u) in rev_topo[i..].iter().enumerate() {
                dp[u].2 = i;
            }
        }
        let u = rev_topo[i];
        for &(v, l) in csr[u].iter() {
            if dp[v].0 < dp[u].0 + 1 || dp[v].0 == dp[u].0 + 1 && dp[v].2 > (l << 32 | dp[u].2) {
                dp[v] = (dp[u].0 + 1, dp[u].1 + l, l << 32 | dp[u].2);
            }
            indeg[v] -= 1;
            if indeg[v] == 0 {
                rev_topo.push(v);
            }
        }
    }
    for (len, sum, _) in dp {
        writeln!(bw, "{len} {sum}").ok();
    }
}
