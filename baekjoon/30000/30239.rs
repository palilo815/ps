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

struct CSR {
    values: Box<[usize]>,
    pref: Box<[usize]>,
}

impl std::ops::Index<usize> for CSR {
    type Output = [usize];
    fn index(&self, i: usize) -> &Self::Output {
        &self.values[self.pref[i]..self.pref[i + 1]]
    }
}

impl CSR {
    fn new(capacity: usize) -> Self {
        Self {
            values: vec![0; capacity * 2].into_boxed_slice(),
            pref: vec![0; capacity + 1].into_boxed_slice(),
        }
    }
    fn build(&mut self, n: usize, edges: &[(usize, usize)]) {
        let values = &mut self.values[..edges.len() * 2];
        let pref = &mut self.pref[..n + 1];
        pref.fill(0);
        for &(u, v) in edges.iter() {
            pref[u] += 1;
            pref[v] += 1;
        }
        for i in 0..n {
            pref[i + 1] += pref[i];
        }
        for &(u, v) in edges.iter() {
            pref[u] -= 1;
            values[pref[u]] = v;
            pref[v] -= 1;
            values[pref[v]] = u;
        }
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    const N: usize = 200_000;
    let t = sc.read::<usize>();
    let mut a = vec![0; N];
    let mut edges = vec![(0, 0); N - 1];
    let mut csr = CSR::new(N);
    let mut topo = Vec::with_capacity(N);
    let mut par = vec![0; N];
    let mut sz = vec![0; N];
    let mut dp = vec![0; N];
    for _ in 0..t {
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        let edges = &mut edges[..n - 1];
        let par = &mut par[..n];
        let sz = &mut sz[..n];
        let dp = &mut dp[..n];
        for x in a.iter_mut() {
            *x = sc.read::<i64>();
        }
        for e in edges.iter_mut() {
            e.0 = sc.read::<usize>() - 1;
            e.1 = sc.read::<usize>() - 1;
        }
        csr.build(n, edges);
        par.fill(usize::MAX);
        par[0] = 0;
        topo.clear();
        topo.push(0);
        for i in 0..n {
            let u = topo[i];
            for &v in csr[u].iter() {
                if par[v] == usize::MAX {
                    par[v] = u;
                    topo.push(v);
                }
            }
        }
        for &u in topo.iter().rev() {
            sz[u] = csr[u].iter().filter(|&&v| v != par[u]).fold(1, |acc, &v| acc + sz[v]);
            dp[u] = csr[u]
                .iter()
                .filter(|&&v| v != par[u])
                .fold(0, |acc, &v| acc + dp[v] + sz[v] * (a[u] ^ a[v]));
        }
        for &u in topo.iter() {
            for &v in csr[u].iter().filter(|&&v| v != par[u]) {
                dp[v] = dp[u] + (n as i64 - sz[v] * 2) * (a[u] ^ a[v]);
            }
        }
        for x in dp.iter() {
            write!(out, "{x} ").ok();
        }
        writeln!(out).ok();
    }
}
