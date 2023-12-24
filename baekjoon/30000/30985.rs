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

#[derive(Eq, PartialEq)]
struct HeapNode(usize, i64);

impl std::cmp::Ord for HeapNode {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.1.cmp(&(self.1))
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
    let k = sc.read::<i64>() - 1;
    let edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<i64>()))
        .collect::<Vec<_>>();
    let csr = CSR::from_undirected_edges(n, edges);
    let e = sc.read_vec::<i64>(n);
    const INF: i64 = 0x3f3f3f3f3f3f3f3f;
    let mut pq = std::collections::BinaryHeap::with_capacity(n);
    let mut dijk = |s: usize| {
        let mut dist = vec![INF; n];
        dist[s] = 0;
        pq.push(HeapNode(s, 0));
        while let Some(HeapNode(u, d)) = pq.pop() {
            if d != dist[u] {
                continue;
            }
            for &(v, w) in csr[u].iter() {
                let d = d + w;
                if dist[v] > d {
                    dist[v] = d;
                    pq.push(HeapNode(v, d));
                }
            }
        }
        dist
    };
    let d1 = dijk(0);
    let d2 = dijk(n - 1);
    let ans = (0..n)
        .map(|i| {
            if e[i] == -1 || d1[i] == INF || d2[i] == INF {
                i64::MAX
            } else {
                d1[i] + d2[i] + k * e[i]
            }
        })
        .min()
        .unwrap();
    writeln!(out, "{}", if ans == i64::MAX { -1 } else { ans }).ok();
}
