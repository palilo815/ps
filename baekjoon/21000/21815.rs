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
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let mut edges = vec![(0, 0, 0); 3 * n];
    for i in (0..3 * n).step_by(3) {
        let c = sc.read::<u32>();
        let p1 = sc.read::<usize>() - 1;
        let p2 = sc.read::<usize>() - 1;
        let p3 = sc.read::<usize>() - 1;
        let p4 = sc.read::<usize>() - 1;
        edges[i] = (p1, p3, c);
        edges[i + 1] = (p1, p2, 0);
        edges[i + 2] = (p3, p4, 0);
    }
    edges.sort_unstable_by(|lhs, rhs| lhs.2.cmp(&rhs.2));
    let mut dsu = DisjointSet::new(n << 1);
    let mut ans = 0;
    for (u, v, c) in edges.into_iter() {
        if dsu.unite(u, v) {
            ans += c;
        }
    }
    writeln!(out, "{}", ans).ok();
}
