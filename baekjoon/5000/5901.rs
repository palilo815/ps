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

fn next_permutation<T: std::cmp::Ord>(data: &mut [T]) -> bool {
    let i = match data.windows(2).rposition(|w| w[0] < w[1]) {
        Some(i) => i,
        None => {
            data.reverse();
            return false;
        }
    };
    let j = data.iter().rposition(|x| data[i] < *x).unwrap();
    data.swap(i, j);
    data[i + 1..].reverse();
    true
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let markets = (0..k).map(|_| sc.read::<usize>() - 1).collect::<Vec<_>>();
    let edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u32>()))
        .collect::<Vec<_>>();
    let csr = Csr::from_undirected_edges(n, edges);
    let mut pq = std::collections::BinaryHeap::with_capacity(m);
    let mut dijk = |s: usize| -> Vec<u32> {
        let mut dist = vec![u32::MAX; n];
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
        dist
    };
    let dist = markets.iter().map(|&s| dijk(s)).collect::<Vec<_>>();
    let mut is_market = vec![false; n];
    markets.iter().for_each(|&s| is_market[s] = true);
    let mut id = (0..k).collect::<Vec<_>>();
    let mut ans = u32::MAX;
    loop {
        let curr = (0..n)
            .filter(|&i| !is_market[i])
            .map(|i| dist[id[0]][i] + dist[id[k - 1]][i])
            .min()
            .unwrap()
            + id.windows(2).map(|w| dist[w[0]][markets[w[1]]]).sum::<u32>();
        ans = ans.min(curr);
        if !next_permutation(&mut id) {
            break;
        }
    }
    writeln!(bw, "{ans}").ok();
}
