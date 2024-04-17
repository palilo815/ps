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
struct HeapNode(i32, usize, usize);

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
    let c = sc.read::<usize>();
    let r = sc.read::<i32>();
    let k = sc.read::<usize>();
    let edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<i32>()))
        .collect::<Vec<_>>();
    let csr = Csr::from_undirected_edges(n, edges);
    let mut pq = (0..c).map(|i| HeapNode(0, i, i)).collect::<std::collections::BinaryHeap<_>>();
    let mut check = vec![[usize::MAX; 10]; n];
    while let Some(HeapNode(d, u, s)) = pq.pop() {
        if check[u].iter().any(|&x| x == s) {
            continue;
        }
        if let Some(it) = check[u].iter_mut().take(k).find(|x| **x == usize::MAX) {
            *it = s;
        } else {
            continue;
        }
        for &(v, w) in csr[u].iter() {
            if d + w <= r && check[v].iter().all(|&x| x != s) && check[v][k - 1] == usize::MAX {
                pq.push(HeapNode(d + w, v, s));
            }
        }
    }
    writeln!(
        bw,
        "{}",
        check.iter().skip(c).filter(|x| x[k - 1] != usize::MAX).count()
    )
    .ok();
    for (i, arr) in check.into_iter().enumerate().skip(c) {
        if arr[k - 1] != usize::MAX {
            writeln!(bw, "{}", i + 1).ok();
        }
    }
}
