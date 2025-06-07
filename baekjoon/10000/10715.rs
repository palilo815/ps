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

#[derive(Eq, PartialEq)]
struct HeapNode<T>(T, usize);

impl<T: Ord> std::cmp::Ord for HeapNode<T> {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0.cmp(&(self.0))
    }
}

impl<T: Ord> std::cmp::PartialOrd for HeapNode<T> {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let c = sc.read::<u64>();
    let edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u64>()))
        .collect::<Vec<_>>();
    let csr = Csr::from_undirected_edges(n, edges.clone());
    let mut dist = vec![u64::MAX; n];
    dist[0] = 0;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(HeapNode(0, 0));
    while let Some(HeapNode(d, u)) = pq.pop() {
        if dist[u] != d {
            continue;
        }
        for &(v, w) in csr[u].iter() {
            if dist[v] > d + w {
                dist[v] = d + w;
                pq.push(HeapNode(d + w, v));
            }
        }
    }
    let total = edges.iter().fold(0, |acc, (_, _, w)| acc + w);
    let mut a = edges.into_iter().map(|(u, v, w)| (dist[u].max(dist[v]), w)).collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    let (ans, _) = a.into_iter().fold((total, total), |(best, sum), (dist, w)| {
        let sum = sum - w;
        (best.min(c * dist + sum), sum)
    });
    writeln!(bw, "{ans}").ok();
}
