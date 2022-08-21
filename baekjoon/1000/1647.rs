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
    let m = sc.read::<usize>();
    let mut edges = (0..m)
        .map(|_| {
            (
                sc.read::<usize>() - 1,
                sc.read::<usize>() - 1,
                sc.read::<u32>(),
            )
        })
        .collect::<Vec<_>>();
    edges.sort_unstable_by(|lhs, rhs| lhs.2.cmp(&rhs.2));
    let mut dsu = DisjointSet::new(n);
    let mut ans = 0;
    let mut need = n - 2;
    for (u, v, w) in edges.into_iter() {
        if dsu.unite(u, v) {
            ans += w;
            need -= 1;
            if need == 0 {
                break;
            }
        }
    }
    writeln!(out, "{}", ans).ok();
}
