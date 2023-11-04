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

#[derive(Eq, PartialEq)]
struct HeapNode(u64, usize);

impl std::cmp::Ord for HeapNode {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0.cmp(&(self.0))
    }
}

impl std::cmp::PartialOrd for HeapNode {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
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
    let p = sc.read::<usize>() - 1;
    let g = sc.read::<usize>() - 1;
    let edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u64>()))
        .collect::<Vec<_>>();
    let csr = CSR::from_undirected_edges(n, edges);
    let mut skip_g = vec![false; n];
    skip_g[p] = true;
    let mut dist = vec![u64::MAX; n];
    dist[p] = 0;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(HeapNode(0, p));
    while let Some(HeapNode(d, u)) = pq.pop() {
        if d != dist[u] {
            continue;
        }
        if u == g {
            skip_g[u] = false;
        }
        for &(v, w) in csr[u].iter() {
            if dist[v] > d + w {
                dist[v] = d + w;
                skip_g[v] = skip_g[u];
                pq.push(HeapNode(d + w, v));
            } else if dist[v] == d + w {
                skip_g[v] |= skip_g[u];
            }
        }
    }
    let target = dist[g] * 2;
    let mut flag = false;
    for i in 0..n {
        if dist[i] == target && !skip_g[i] {
            write!(out, "{} ", i + 1).ok();
            flag = true;
        }
    }
    if !flag {
        writeln!(out, "*").ok();
    }
}
