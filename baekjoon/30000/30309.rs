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

impl<T: Clone + Copy + Default> CSR<T> {
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

#[derive(PartialEq)]
struct HeapNode(f64, usize);

impl Eq for HeapNode {}

impl std::cmp::Ord for HeapNode {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        self.partial_cmp(rhs).unwrap()
    }
}

impl std::cmp::PartialOrd for HeapNode {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        rhs.0.partial_cmp(&self.0)
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
    let t = sc.read::<f64>();
    let edges = (0..m)
        .map(|_| {
            (
                sc.read::<usize>() - 1,
                sc.read::<usize>() - 1,
                (sc.read::<f64>(), sc.read::<f64>()),
            )
        })
        .collect::<Vec<_>>();
    let csr = CSR::from_undirected_edges(n, edges);
    let parametric = |mut lo, mut hi| {
        let mut pq = std::collections::BinaryHeap::with_capacity(m);
        let mut dist = vec![0.0; n];
        let mut f = |mid| -> bool {
            dist.fill(f64::MAX);
            dist[0] = 0.0;
            pq.push(HeapNode(0.0, 0));
            while let Some(HeapNode(d, u)) = pq.pop() {
                if d != dist[u] {
                    continue;
                }
                for &(v, (len, lim)) in csr[u].iter() {
                    let d = d + len / (lim + mid);
                    if dist[v] > d {
                        dist[v] = d;
                        pq.push(HeapNode(d, v));
                    }
                }
            }
            dist[n - 1] <= t
        };
        // first true
        while hi - lo > 1e-6 {
            let mid = (lo + hi) / 2.0;
            if f(mid) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        lo
    };
    writeln!(out, "{:.7}", parametric(0.0, 1e9)).ok();
}
