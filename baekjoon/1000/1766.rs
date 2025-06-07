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
    fn from_direct_edges(n: usize, edges: Vec<(usize, usize, T)>) -> Self {
        let mut values = vec![(0, T::default()); edges.len()].into_boxed_slice();
        let mut pref = vec![0; n + 1].into_boxed_slice();
        for &(u, _, _) in edges.iter() {
            pref[u] += 1;
        }
        for i in 0..n {
            pref[i + 1] += pref[i];
        }
        for (u, v, w) in edges {
            pref[u] -= 1;
            values[pref[u]] = (v, w);
        }
        Self { values, pref }
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let edges = (0..m).map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, ())).collect::<Vec<_>>();
    let mut pre = vec![0; n];
    for &(_, v, _) in edges.iter() {
        pre[v] += 1;
    }
    let csr = Csr::from_direct_edges(n, edges);
    let mut pq = (0..n)
        .filter_map(|i| if pre[i] == 0 { Some(std::cmp::Reverse(i)) } else { None })
        .collect::<std::collections::BinaryHeap<_>>();
    while let Some(std::cmp::Reverse(u)) = pq.pop() {
        write!(bw, "{} ", u + 1).ok();
        for &(v, _) in csr[u].iter() {
            pre[v] -= 1;
            if pre[v] == 0 {
                pq.push(std::cmp::Reverse(v));
            }
        }
    }
}
