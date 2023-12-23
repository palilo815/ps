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
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let edges = (0..m).map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, ())).collect::<Vec<_>>();
    let csr = CSR::from_undirected_edges(n, edges);
    let mut dq = std::collections::VecDeque::new();
    dq.push_back(0);
    let mut dist = vec![-1; n];
    dist[0] = 0;
    while let Some(u) = dq.pop_front() {
        for &(v, _) in csr[u].iter() {
            if dist[v] == -1 {
                dist[v] = dist[u] + 1;
                dq.push_back(v)
            }
        }
    }
    writeln!(out, "{}", dist.last().unwrap() - 1).ok();
}
