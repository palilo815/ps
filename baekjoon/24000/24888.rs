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
    fn with_undirected_edges(n: usize, edges: Vec<(usize, usize, T)>) -> Self {
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
struct HeapNode(usize, u64);

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
    let edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u64>()))
        .collect::<Vec<_>>();
    let csr = CSR::with_undirected_edges(n, edges);
    const INF: u64 = 0x3f3f3f3f3f3f3f3f;
    let mut dist = vec![INF; n];
    dist[0] = 0;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(HeapNode(0, 0));
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
    let note = (0..n).map(|_| sc.read::<usize>() == 1).collect::<Vec<_>>();
    let mut ids = (0..n).collect::<Vec<_>>();
    ids.sort_unstable_by(|&l, &r| dist[l].cmp(&dist[r]));
    let mut prv = vec![0; n];
    let mut dp = vec![-1; n];
    dp[0] = 0;
    for u in ids.into_iter() {
        if note[u] {
            dp[u] += 1;
        }
        for &(v, w) in csr[u].iter() {
            if dist[u] + w == dist[v] && dp[v] < dp[u] {
                dp[v] = dp[u];
                prv[v] = u;
            }
        }
    }
    if dp[n - 1] != note.into_iter().filter(|&x| x).count() as i32 {
        writeln!(out, "-1").ok();
        return;
    }
    let mut trace = Vec::with_capacity(n);
    let mut u = n - 1;
    while u != 0 {
        trace.push(u);
        u = prv[u];
    }
    trace.push(0);
    writeln!(out, "{}", trace.len()).ok();
    for x in trace.into_iter().rev() {
        write!(out, "{} ", x + 1).ok();
    }
}
