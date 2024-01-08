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
struct HeapNode(i32, usize);

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
    let edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<i32>()))
        .collect::<Vec<_>>();
    let csr = CSR::from_undirected_edges(n, edges);
    let s = sc.read::<usize>() - 1;
    let e = sc.read::<usize>() - 1;
    let mut pq = std::collections::BinaryHeap::with_capacity(m);
    let mut dijk = |src: usize, mut dist: Vec<i32>| {
        dist[src] = 0;
        pq.push(HeapNode(0, src));
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
        dist
    };
    const INF: i32 = 0x3f3f3f3f;
    let d1 = dijk(s, vec![INF; n]);
    let mut mask = vec![0; n];
    let mut stack = Vec::with_capacity(n);
    stack.push(e);
    while let Some(u) = stack.pop() {
        for &(v, w) in csr[u].iter() {
            if mask[v] == 0 && d1[v] + w == d1[u] {
                mask[v] = 1;
                stack.push(v);
            }
        }
    }
    mask[e] = 1;
    let mut u = s;
    while u != e {
        mask[u] = 2;
        u = csr[u]
            .iter()
            .filter(|e| mask[e.0] == 1 && d1[u] + e.1 == d1[e.0])
            .map(|e| e.0)
            .min()
            .unwrap();
    }
    mask[s] = 0;
    let dist = (0..n).map(|i| if mask[i] == 2 { 0 } else { INF }).collect::<Vec<_>>();
    let d2 = dijk(e, dist);
    writeln!(out, "{}", d1[e] + d2[s]).ok();
}
