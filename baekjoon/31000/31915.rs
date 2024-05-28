use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
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
struct HeapNode(u64, usize, usize);

impl std::cmp::Ord for HeapNode {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0.cmp(&self.0).then(rhs.1.cmp(&self.1))
    }
}

impl std::cmp::PartialOrd for HeapNode {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u64>()))
        .collect::<Vec<_>>();
    let csr = Csr::from_undirected_edges(n, edges);
    let mut pq = std::collections::BinaryHeap::new();
    let mut dp = vec![[(u64::MAX, usize::MAX); 2]; n];
    for (i, x) in dp.iter_mut().enumerate().take(k) {
        pq.push(HeapNode(0, i, i));
        x[0] = (0, i);
    }
    while let Some(HeapNode(d, s, u)) = pq.pop() {
        if (d, s) != dp[u][0] && (d, s) != dp[u][1] {
            continue;
        }
        for &(v, w) in csr[u].iter() {
            let d = d + w;
            if let Some(x) = dp[v].iter_mut().find(|x| x.1 == s) {
                if d < x.0 {
                    x.0 = d;
                    pq.push(HeapNode(d, s, v));
                    if dp[v][0] > dp[v][1] {
                        dp[v].swap(0, 1);
                    }
                }
            } else if (d, s) < dp[v][0] {
                dp[v][1] = dp[v][0];
                dp[v][0] = (d, s);
                pq.push(HeapNode(d, s, v));
            } else if (d, s) < dp[v][1] {
                dp[v][1] = (d, s);
                pq.push(HeapNode(d, s, v));
            }
        }
    }
    for dp in dp.into_iter().skip(k) {
        write!(bw, "{} ", dp[1].0).ok();
    }
}
