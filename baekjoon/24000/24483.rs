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

impl<T> std::ops::IndexMut<usize> for Csr<T> {
    fn index_mut(&mut self, i: usize) -> &mut Self::Output {
        &mut self.values[self.pref[i]..self.pref[i + 1]]
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
    let s = sc.read::<usize>() - 1;
    let edges = (0..m).map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, ())).collect::<Vec<_>>();
    let mut csr = Csr::from_undirected_edges(n, edges);
    for i in 0..n {
        csr[i].sort_unstable_by(|l, r| r.0.cmp(&l.0));
    }
    let mut dep = vec![-1; n];
    let mut stack = vec![s];
    let mut tick = 0;
    let mut ans = 0;
    while let Some(u) = stack.pop() {
        if dep[u] != -1 {
            continue;
        }
        tick += 1;
        dep[u] = csr[u].iter().map(|&(v, _)| dep[v]).max().unwrap_or(-1) + 1;
        ans += tick * dep[u] as i64;
        for &(v, _) in csr[u].iter() {
            if dep[v] == -1 {
                stack.push(v);
            }
        }
    }
    writeln!(bw, "{ans}").ok();
}
