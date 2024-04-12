use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
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
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let edges = (1..n)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u32>()))
        .collect::<Vec<_>>();
    let csr = Csr::from_undirected_edges(n, edges);
    let mut topo = Vec::with_capacity(n);
    topo.push(0);
    let mut dist = vec![0; n];
    dist[0] = u32::MAX;
    for i in 0..n {
        let u = topo[i];
        for &(v, w) in csr[u].iter() {
            if dist[v] == 0 {
                dist[v] = w;
                topo.push(v);
            }
        }
    }
    let mut dp = vec![0; n];
    for u in topo.into_iter().rev() {
        let acc = csr[u].iter().fold(0, |acc, e| acc + dp[e.0]);
        dp[u] = if acc == 0 { dist[u] } else { dist[u].min(acc) };
    }
    writeln!(out, "{}", dp[0]).ok();
}
