use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = Vec::new();
        stdin().lock().read_to_end(&mut buf).ok();
        let s = unsafe { std::str::from_utf8_unchecked(Box::leak(buf.into_boxed_slice())) };
        Self { it: s.split_ascii_whitespace() }
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
    let edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u32>()))
        .collect();
    let csr = Csr::from_directed_edges(n, edges);
    let s = sc.read::<usize>() - 1;
    let t = sc.read::<usize>() - 1;
    let mut colour = vec![0; n];
    let mut dist = vec![u32::MAX; n];
    dist[s] = 0;
    let mut dq = std::collections::VecDeque::new();
    dq.push_back(s);
    while let Some(u) = dq.pop_front() {
        colour[u] = 2;
        for &(v, w) in csr[u].iter() {
            if dist[v] > dist[u] + w {
                dist[v] = dist[u] + w;
                if colour[v] == 0 {
                    colour[v] = 1;
                    dq.push_back(v);
                } else if colour[v] == 2 {
                    colour[v] = 1;
                    dq.push_front(v);
                }
            }
        }
    }
    writeln!(bw, "{}", dist[t]).ok();
}
