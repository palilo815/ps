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
    fn from_directed_edges(n: usize, edges: Vec<(usize, usize, T)>) -> Self {
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
    let a = sc.read::<usize>() - 1;
    let b = sc.read::<usize>() - 1;
    let c = sc.read::<i32>();
    let edges = (0..m).map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, ())).collect::<Vec<_>>();
    let csr = Csr::from_directed_edges(n, edges);
    let mut dq = std::collections::VecDeque::new();
    let mut bfs = |s: usize| -> Vec<i32> {
        let mut dist = vec![i32::MAX; n];
        dist[s] = 0;
        dq.push_back(s);
        while let Some(u) = dq.pop_front() {
            for &(v, _) in csr[u].iter() {
                if dist[v] == i32::MAX {
                    dist[v] = dist[u] + 1;
                    dq.push_back(v);
                }
            }
        }
        dist
    };
    let d1 = bfs(0);
    let d2 = bfs(b);
    let res1 = d1[n - 1];
    let res2 = if d1[a] != i32::MAX && d2[n - 1] != i32::MAX {
        d1[a] + d2[n - 1] - c
    } else {
        i32::MAX
    };
    if res1 == i32::MAX && res2 == i32::MAX {
        writeln!(bw, "x").ok();
    } else if res2 != i32::MAX && c > d2[a] {
        writeln!(bw, "-inf").ok();
    } else {
        writeln!(bw, "{}", res1.min(res2)).ok();
    }
}
