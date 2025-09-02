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
    fn with_capacity(n: usize, m: usize) -> Self {
        Self {
            values: vec![(0, T::default()); m * 2].into(),
            pref: vec![0; n + 1].into(),
        }
    }
    fn init_undirected_edges(&mut self, n: usize, edges: &[(usize, usize, T)]) {
        let values = &mut self.values;
        let pref = &mut self.pref[..n + 1];
        pref.fill(0);
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
    const N: usize = 2_000;
    const M: usize = 50_000;
    let mut csr = Csr::with_capacity(N, M);
    let mut edges = vec![(0, 0, 0); M];
    let mut dist = vec![0; N];
    let mut pq = std::collections::BinaryHeap::new();
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        let t = sc.read::<usize>();
        let s = sc.read::<usize>() - 1;
        let g = sc.read::<usize>() - 1;
        let h = sc.read::<usize>() - 1;
        let edges = &mut edges[..m];
        edges.fill_with(|| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u32>() * 2));
        let target = edges.iter_mut().find(|e| e.0 == g && e.1 == h || e.0 == h && e.1 == g).unwrap();
        target.2 -= 1;
        csr.init_undirected_edges(n, edges);
        let dist = &mut dist[..n];
        dist.fill(u32::MAX - 1); // even
        dist[s] = 0;
        pq.push(HeapNode(0, s));
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
        let mut destinations = (0..t).map(|_| sc.read::<usize>()).filter(|&v| dist[v - 1] & 1 == 1).collect::<Vec<_>>();
        destinations.sort_unstable();
        for x in destinations {
            write!(bw, "{x} ").ok();
        }
        writeln!(bw).ok();
    }
}
