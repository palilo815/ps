use std::{collections::VecDeque, io::*};

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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
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
    let m = sc.read::<usize>();
    let x = sc.read::<usize>();
    let y = sc.read::<usize>();
    let a = sc.read_vec::<u32>(n);
    let csr = CSR::from_undirected_edges(
        n,
        (0..m).map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, ())).collect(),
    );
    let mut q = (0..y).map(|_| sc.read::<usize>() - 1).collect::<VecDeque<_>>();
    let mut dist = vec![u64::MAX; n];
    for &s in q.iter() {
        dist[s] = 0;
    }
    while let Some(u) = q.pop_front() {
        for &(v, _) in csr[u].iter() {
            if dist[v] == u64::MAX {
                dist[v] = dist[u] + 1;
                q.push_back(v);
            }
        }
    }
    for i in 0..n {
        if dist[i] == u64::MAX && a[i] != 0 {
            writeln!(out, "-1").ok();
            return;
        }
    }
    for (d, a) in dist.iter_mut().zip(a.into_iter()) {
        *d *= a as u64;
    }
    dist.select_nth_unstable(n - x);
    writeln!(out, "{}", dist.into_iter().rev().take(x).sum::<u64>()).ok();
}
