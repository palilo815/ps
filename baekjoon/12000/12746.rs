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
    let q = sc.read::<usize>();
    let edges = (1..n).map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, ())).collect::<Vec<_>>();
    let csr = Csr::from_undirected_edges(n, edges);
    let mut topo = Vec::with_capacity(n);
    topo.push(0);
    let mut par = vec![usize::MAX - 1; n];
    par[0] = usize::MAX;
    for i in 0..n {
        let u = topo[i];
        for &(v, _) in csr[u].iter() {
            if par[v] == usize::MAX - 1 {
                par[v] = u;
                topo.push(v);
            }
        }
    }
    let mut sub = vec![1; n];
    topo.iter().skip(1).rev().for_each(|&u| sub[par[u]] += sub[u]);
    let mut top = vec![0; n];
    for i in 0..n {
        let u = topo[i];
        if let Some(&(heavy, _)) = csr[u].iter().filter(|v| v.0 != par[u]).max_by_key(|v| sub[v.0]) {
            top[heavy] = top[u];
            topo[i + 1] = heavy;
            csr[u]
                .iter()
                .filter(|v| v.0 != heavy && v.0 != par[u])
                .fold(sub[heavy] + 1, |acc, &(v, _)| {
                    top[v] = v;
                    topo[i + acc] = v;
                    acc + sub[v]
                });
        }
    }
    let mut tin = vec![0; n];
    topo.iter().enumerate().for_each(|(i, &u)| tin[u] = i);
    let mut imos = vec![0; n + 1];
    for _ in 0..q {
        let mut u = sc.read::<usize>() - 1;
        let mut v = sc.read::<usize>() - 1;
        while top[u] != top[v] {
            if sub[top[u]] > sub[top[v]] {
                std::mem::swap(&mut u, &mut v);
            }
            imos[tin[top[u]]] += 1;
            imos[tin[u] + 1] -= 1;
            u = par[top[u]];
        }
        if tin[u] > tin[v] {
            std::mem::swap(&mut u, &mut v);
        }
        imos[tin[u] + 1] += 1;
        imos[tin[v] + 1] -= 1;
    }
    for i in 0..n {
        imos[i + 1] += imos[i];
    }
    let (ans, u, v) = topo
        .into_iter()
        .enumerate()
        .map(|(i, u)| {
            let v = par[u];
            let w = imos[i];
            (-w, u.min(v), u.max(v))
        })
        .min()
        .unwrap();
    writeln!(bw, "{} {} {}", u + 1, v + 1, -ans).ok();
}
