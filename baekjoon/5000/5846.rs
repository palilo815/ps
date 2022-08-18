use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

struct DisjointSet {
    p: Vec<i32>,
}

impl DisjointSet {
    fn new(n: usize) -> Self {
        Self { p: vec![-1; n] }
    }
    fn find(&mut self, u: usize) -> usize {
        if self.p[u] < 0 {
            u
        } else {
            let rt = self.find(self.p[u] as usize);
            self.p[u] = rt as i32;
            rt
        }
    }
    fn unite(&mut self, u: usize, v: usize) -> bool {
        let mut u = self.find(u);
        let mut v = self.find(v);
        if u == v {
            return false;
        }
        if self.p[u] > self.p[v] {
            std::mem::swap(&mut u, &mut v);
        }
        self.p[u] += self.p[v];
        self.p[v] = u as i32;
        true
    }
    fn size_of(&mut self, u: usize) -> usize {
        let root = self.find(u);
        (-self.p[root]) as usize
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let grid = (0..n).map(|_| sc.read_vec::<i32>(n)).collect::<Vec<_>>();
    let mut edges = Vec::with_capacity(n * (n - 1) * 2);
    for i in 0..n {
        for j in 0..n {
            if i + 1 != n {
                edges.push((
                    i * n + j,
                    (i + 1) * n + j,
                    (grid[i][j] - grid[i + 1][j]).abs(),
                ));
            }
            if j + 1 != n {
                edges.push((
                    i * n + j,
                    i * n + j + 1,
                    (grid[i][j] - grid[i][j + 1]).abs(),
                ));
            }
        }
    }
    edges.sort_unstable_by(|lhs, rhs| lhs.2.cmp(&rhs.2));
    let mut dsu = DisjointSet::new(n * n);
    for (u, v, w) in edges.into_iter() {
        if dsu.unite(u, v) && dsu.size_of(u) * 2 >= n * n {
            writeln!(out, "{}", w).ok();
            return;
        }
    }
}
