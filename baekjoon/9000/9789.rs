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
    let edges = (0..m).map(|_| (sc.read::<usize>(), sc.read::<usize>(), ())).collect();
    let csr = Csr::from_directed_edges(n, edges);
    let mut stk = Vec::with_capacity(n);
    let mat = (0..n)
        .map(|s| {
            let mut visited = vec![0; n];
            visited[s] = 1;
            stk.push(s);
            while let Some(u) = stk.pop() {
                for &(v, _) in csr[u].iter() {
                    if visited[v] == 0 {
                        visited[v] = 1;
                        stk.push(v);
                    }
                }
            }
            visited
        })
        .collect::<Vec<_>>();
    let q = sc.read::<usize>();
    for _ in 0..q {
        let u = sc.read::<usize>();
        let v = sc.read::<usize>();
        writeln!(bw, "{}", mat[u][v]).ok();
    }
}
