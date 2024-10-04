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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

struct BipartiteMatching {
    n: usize,
    m: usize,
    adj: Vec<Vec<usize>>,
}

impl BipartiteMatching {
    fn new(n: usize, m: usize) -> Self {
        Self { n, m, adj: vec![vec![]; n] }
    }
    fn add_edge(&mut self, u: usize, v: usize) {
        assert!(u < self.n && v < self.m);
        self.adj[u].push(v);
    }
    fn maximum_matching(&self) -> Vec<usize> {
        let mut check = vec![false; self.n];
        let mut wife = vec![usize::MAX; self.n];
        let mut hubby = vec![usize::MAX; self.m];
        while (0..self.n).any(|i| wife[i] == usize::MAX && self._dfs(i, &mut check, &mut wife, &mut hubby)) {
            check.fill(false);
        }
        wife
    }
    fn _dfs(&self, u: usize, check: &mut [bool], wife: &mut [usize], hubby: &mut [usize]) -> bool {
        check[u] = true;
        for &v in self.adj[u].iter() {
            if hubby[v] == usize::MAX || (!check[hubby[v]] && self._dfs(hubby[v], check, wife, hubby)) {
                wife[u] = v;
                hubby[v] = u;
                return true;
            }
        }
        false
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let m = sc.read::<usize>();
    let n = sc.read::<usize>();
    let mut s = (0..n).map(|_| (sc.read_vec::<i32>(m))).collect::<Vec<_>>();
    let mut t = (0..n).map(|_| (sc.read_vec::<i32>(m))).collect::<Vec<_>>();
    for (x, y) in s.iter_mut().flatten().zip(t.iter_mut().flatten()) {
        if x == y {
            *x = 0;
            *y = 0;
        }
    }
    let mut c1 = 0;
    let mut c2 = 0;
    for x in s.iter_mut().flatten() {
        if *x == 0 {
            *x = -1;
        } else {
            *x = c1;
            c1 += 1;
        }
    }
    for x in t.iter_mut().flatten() {
        if *x == 0 {
            *x = -1;
        } else {
            *x = c2;
            c2 += 1;
        }
    }
    if c1 != c2 {
        writeln!(bw, "-1").ok();
        return;
    }
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let mut kuhn = BipartiteMatching::new(c1 as usize, c2 as usize);
    for i in 0..n {
        for j in 0..m {
            if s[i][j] != -1 {
                for &(di, dj) in MOVE.iter() {
                    let ii = i + di;
                    let jj = j + dj;
                    if ii < n && jj < m && t[ii][jj] != -1 {
                        kuhn.add_edge(s[i][j] as usize, t[ii][jj] as usize);
                    }
                }
            }
        }
    }
    let matching = kuhn.maximum_matching().into_iter().filter(|&x| x != usize::MAX).count() as i32;
    writeln!(bw, "{}", matching + (c1 - matching) * 2).ok();
}
