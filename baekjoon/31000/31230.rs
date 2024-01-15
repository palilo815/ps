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
    let a = sc.read::<usize>() - 1;
    let b = sc.read::<usize>() - 1;
    let edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u64>()))
        .collect();
    let csr = Csr::from_undirected_edges(n, edges);
    let mut dist = vec![u64::MAX; n];
    dist[a] = 0;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(HeapNode(0, a));
    while let Some(HeapNode(d, u)) = pq.pop() {
        if d != dist[u] {
            continue;
        }
        for &(v, w) in csr[u].iter() {
            let d = d + w;
            if dist[v] > d {
                dist[v] = d;
                pq.push(HeapNode(d, v));
            }
        }
    }
    let mut check = vec![false; n];
    check[b] = true;
    let mut stack = vec![b];
    while let Some(v) = stack.pop() {
        for &(u, w) in csr[v].iter() {
            if dist[u] + w == dist[v] && !check[u] {
                check[u] = true;
                stack.push(u);
            }
        }
    }
    writeln!(out, "{}", check.iter().filter(|&&x| x).count()).ok();
    for (i, _) in check.into_iter().enumerate().filter(|x| x.1) {
        write!(out, "{} ", i + 1).ok();
    }
}
