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
    let edges = (1..n).map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, ())).collect();
    let csr = Csr::from_undirected_edges(n, edges);
    let mut stack = Vec::with_capacity(n);
    let mut dfs = |s: usize, dist: &mut [i32]| {
        dist.fill(-1);
        dist[s] = 0;
        stack.push(s);
        while let Some(u) = stack.pop() {
            let d = dist[u];
            for &(v, _) in csr[u].iter() {
                if dist[v] == -1 {
                    dist[v] = d + 1;
                    stack.push(v);
                }
            }
        }
    };
    let mut dist = vec![0; n];
    dfs(0, &mut dist);
    let s = dist.iter().enumerate().max_by_key(|x| x.1).map(|x| x.0).unwrap();
    dfs(s, &mut dist);
    let dia = dist.into_iter().max().unwrap();
    writeln!(bw, "{}", (dia + 1) / 2).ok();
}
