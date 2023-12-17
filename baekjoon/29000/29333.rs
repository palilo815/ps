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

struct CSR<T> {
    values: Box<[(usize, T)]>,
    pref: Box<[usize]>,
}

impl<T> std::ops::Index<usize> for CSR<T> {
    type Output = [(usize, T)];
    fn index(&self, i: usize) -> &Self::Output {
        &self.values[self.pref[i]..self.pref[i + 1]]
    }
}

impl<T: Copy + Default> CSR<T> {
    fn from_undirected_edges(n: usize, edges: &Vec<(usize, usize, T)>) -> Self {
        let mut values = vec![(0, T::default()); edges.len() * 2].into_boxed_slice();
        let mut pref = vec![0; n + 1].into_boxed_slice();
        for &(u, v, _) in edges.iter() {
            pref[u] += 1;
            pref[v] += 1;
        }
        for i in 0..n {
            pref[i + 1] += pref[i];
        }
        for &(u, v, w) in edges.iter() {
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
    let m = sc.read::<usize>();
    let s = sc.read::<usize>() - 1;
    let e = sc.read::<usize>() - 1;
    let edges = (0..m).map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, ())).collect::<Vec<_>>();
    let csr = CSR::from_undirected_edges(n, &edges);
    let mut par = vec![usize::MAX; n];
    let mut is_walk = vec![false; n];
    par[s] = s;
    let mut dq = std::collections::VecDeque::new();
    dq.push_back(s);
    while let Some(u) = dq.pop_front() {
        for &(v, _) in csr[u].iter() {
            if par[v] == usize::MAX {
                par[v] = u;
                dq.push_back(v);
            }
        }
    }
    if par[e] == usize::MAX {
        writeln!(out, "-1").ok();
        return;
    }
    let mut u = e;
    while u != s {
        is_walk[u] = true;
        u = par[u];
    }
    is_walk[s] = true;
    for (u, v, _) in edges {
        let d = if is_walk[u] && is_walk[v] {
            (par[u] == v).into()
        } else if is_walk[u] ^ is_walk[v] {
            is_walk[u].into()
        } else {
            0 // no matter
        };
        write!(out, "{d} ").ok();
    }
}
