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
struct HeapNode(u32, usize);

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
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let edges = (0..m).map(|_| (sc.read::<usize>(), sc.read::<usize>(), sc.read::<u32>())).collect();
    let csr = Csr::from_undirected_edges(n, edges);
    let mut pq = std::collections::BinaryHeap::new();
    let mut d1 = vec![u32::MAX; n];
    let mut d2 = vec![u32::MAX; n];
    let mut visited = vec![false; n];
    for _ in 0..k {
        let x = sc.read::<usize>();
        d1[x] = 0;
        d2[x] = 0;
        pq.push(HeapNode(0, x));
    }
    loop {
        let HeapNode(d, u) = pq.pop().unwrap();
        if u == 0 {
            writeln!(bw, "{d}").ok();
            break;
        }
        if std::mem::replace(&mut visited[u], true) {
            continue;
        }
        for &(v, w) in csr[u].iter() {
            if d1[v] > d + w {
                d2[v] = std::mem::replace(&mut d1[v], d + w);
                if d2[v] != u32::MAX {
                    pq.push(HeapNode(d2[v], v));
                }
            } else if d2[v] > d + w {
                d2[v] = d + w;
                pq.push(HeapNode(d2[v], v));
            }
        }
    }
}
