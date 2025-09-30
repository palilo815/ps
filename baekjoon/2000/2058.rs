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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
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
    let m = sc.read::<usize>();
    let atom = sc.read_vec::<i32>(n);
    let proton = (0..m).map(|_| sc.read::<u32>()).collect::<std::collections::HashSet<_>>();
    let mut edges = vec![];
    for i in 0..n {
        for j in 0..i {
            if proton.contains(&(atom[i].abs_diff(atom[j]))) {
                edges.push((i, j, ()));
            }
        }
    }
    let csr = Csr::from_undirected_edges(n, edges);
    let mut par = vec![usize::MAX; n];
    let mut stack = vec![];
    let mut ptr = 0;
    for i in 0..n {
        if par[i] != usize::MAX {
            continue;
        }
        par[i] = usize::MAX - 1;
        stack.push(i);
        while ptr < stack.len() {
            let u = stack[ptr];
            ptr += 1;
            for &(v, _) in csr[u].iter() {
                if par[v] == usize::MAX {
                    par[v] = u;
                    stack.push(v);
                }
            }
        }
    }
    assert_eq!(stack.len(), n);
    let mut dp = vec![(0, 0); n];
    for u in stack.into_iter().rev() {
        dp[u].1 += atom[u];
        if par[u] != usize::MAX - 1 {
            dp[par[u]].0 += dp[u].0.max(dp[u].1);
            dp[par[u]].1 += dp[u].0;
        }
    }
    let ans = (0..n).filter(|&i| par[i] == usize::MAX - 1).map(|i| dp[i].0.max(dp[i].1)).sum::<i32>();
    writeln!(bw, "{ans}").ok();
}
