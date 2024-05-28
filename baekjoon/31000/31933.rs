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

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let edges = (0..m)
        .map(|_| {
            (
                sc.read::<usize>() - 1,
                sc.read::<usize>() - 1,
                (sc.read::<u32>(), sc.read::<u32>() + 1),
            )
        })
        .collect::<Vec<_>>();
    let mut values = vec![0; m << 1 | 1]; // values[2m] is sentinel
    for i in 0..m {
        values[i << 1] = edges[i].2 .0;
        values[i << 1 | 1] = edges[i].2 .1;
    }
    values.sort_unstable();
    values.dedup();
    let csr = Csr::from_undirected_edges(n, edges);
    let mut stack = Vec::with_capacity(n);
    let mut visited = vec![false; n];
    let mut dfs = |fish: u32| -> bool {
        stack.clear();
        stack.push(0);
        visited[1..].fill(false);
        while let Some(u) = stack.pop() {
            for &(v, (l, r)) in csr[u].iter() {
                if l <= fish && fish < r && !visited[v] {
                    if v == n - 1 {
                        return true;
                    }
                    visited[v] = true;
                    stack.push(v);
                }
            }
        }
        false
    };
    let ok = values.iter().map(|&v| dfs(v)).collect::<Vec<_>>();
    let k = sc.read::<usize>();
    let ans = (0..k)
        .filter(|_| {
            let fish = sc.read::<u32>();
            let i = values.partition_point(|&x| x <= fish);
            ok[i - 1]
        })
        .count();
    writeln!(bw, "{ans}").ok();
}
