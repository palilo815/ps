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
    let edges = (1..n).map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, ())).collect::<Vec<_>>();
    let csr = Csr::from_undirected_edges(n, edges);
    let mut nuts = vec![false; n];
    for _ in 0..m {
        nuts[sc.read::<usize>() - 1] = true;
    }
    let mut ans = 0;
    let mut visited = vec![false; n];
    let mut stack = Vec::with_capacity(n);
    stack.push(0);
    while let Some(u) = stack.pop() {
        if nuts[u] {
            let mut vacants = csr[u].iter().filter(|&&(v, _)| !visited[v] && !nuts[v]);
            if let Some(&(v, _)) = vacants.next() {
                if vacants.next().is_none() {
                    nuts[v] = true;
                }
            } else {
                continue;
            }
        }
        visited[u] = true;
        ans += 1;
        stack.extend(csr[u].iter().map(|e| e.0).filter(|&v| !visited[v]));
    }
    writeln!(bw, "{ans}").ok();
}
