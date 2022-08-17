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
    let a = sc.read_vec::<u32>(n);
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut ids = (0..n).collect::<Vec<_>>();
    ids.sort_unstable_by(|&lhs, &rhs| a[rhs].cmp(&a[lhs]));
    let mut alive = vec![false; n];
    let mut dsu = DisjointSet::new(n);
    let mut ans = 0;
    for u in ids.into_iter() {
        alive[u] = true;
        for &v in adj[u].iter().filter(|&&x| alive[x]) {
            dsu.unite(u, v);
        }
        ans = ans.max(a[u] as u64 * dsu.size_of(u) as u64);
    }
    writeln!(out, "{}", ans).ok();
}
