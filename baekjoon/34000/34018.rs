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
    fn from_directed_edges(n: usize, edges: Vec<(usize, usize, T)>) -> Self {
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
    let mut t = vec![0; n];
    t[1..].fill_with(|| sc.read::<u64>());
    let edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u64>()))
        .collect::<Vec<_>>();
    let csr = Csr::from_directed_edges(n, edges);
    let mut dist = vec![u32::MAX; n];
    dist[0] = 0;
    let mut best = vec![(u64::MAX, 0); n];
    best[0] = (0, 0);
    let mut dq = std::collections::VecDeque::with_capacity(m);
    dq.push_back(0);
    while let Some(u) = dq.pop_front() {
        let d = dist[u] + 1;
        let c = best[u];
        for &(v, w) in csr[u].iter() {
            if dist[v] == u32::MAX {
                dist[v] = d;
                dq.push_back(v);
            }
            if dist[v] == d {
                best[v].0 = best[v].0.min(c.0 + w + t[v]);
                best[v].1 = best[v].1.max(c.1 + w + t[v]);
            }
        }
    }
    let mut ans = u32::MAX;
    let mut min = u64::MAX;
    let mut max = 0;
    for u in 1..n {
        if dist[u] > ans {
            continue;
        }
        for &(v, w) in csr[u].iter() {
            if v == 0 {
                if dist[u] < ans {
                    ans = dist[u];
                    min = best[u].0 + w;
                    max = best[u].1 + w;
                } else if dist[u] == ans {
                    min = min.min(best[u].0 + w);
                    max = max.max(best[u].1 + w);
                }
            }
        }
    }
    writeln!(bw, "{min}\n{max}").ok();
}
