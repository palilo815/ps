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

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let edges = (0..m).map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, ())).collect::<Vec<_>>();
    let csr = Csr::from_undirected_edges(n, edges);
    let cycle = (0..k).map(|_| sc.read::<usize>() - 1).collect::<Vec<_>>();
    let mut dq = std::collections::VecDeque::new();
    dq.push_back((0, 0));
    let mut dist = vec![vec![usize::MAX; k]; n];
    dist[0][0] = 0;
    while let Some((u, i)) = dq.pop_front() {
        let j = if i + 1 == k { 0 } else { i + 1 };
        let d = dist[u][i] + 1;
        if cycle[i] == u {
            let v = cycle[j];
            if dist[v][j] == usize::MAX {
                dist[v][j] = d;
                dq.push_back((v, j));
            }
            continue;
        }
        if dist[u][j] == usize::MAX {
            dist[u][j] = d;
            dq.push_back((u, j));
        }
        for &(v, _) in csr[u].iter() {
            if dist[v][j] == usize::MAX {
                dist[v][j] = d;
                dq.push_back((v, j));
            }
        }
    }
    let ans = *dist[n - 1].iter().min().unwrap();
    writeln!(bw, "{}", ans as isize).ok();
}
