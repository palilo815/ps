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

struct DisjointSet {
    p: Vec<i32>,
}

impl DisjointSet {
    fn new(n: usize) -> Self {
        Self { p: vec![-1; n] }
    }
    fn clear(&mut self) {
        self.p.fill(-1);
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

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let mut dsu = DisjointSet::new(10_000);
    let mut edges = [(0, 0, 0); 20_000];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let _ = sc.read::<usize>();
        let m = sc.read::<usize>();
        let p = sc.read::<usize>() - 1;
        let q = sc.read::<usize>() - 1;
        let edges = &mut edges[..m];
        for e in edges.iter_mut() {
            e.0 = sc.read::<usize>() - 1;
            e.1 = sc.read::<usize>() - 1;
            e.2 = sc.read::<u32>();
        }
        edges.sort_unstable_by(|l, r| l.2.cmp(&r.2));
        let k = if let Some(i) = edges
            .iter()
            .position(|e| e.0 == p && e.1 == q || e.0 == q && e.1 == p)
        {
            let j = edges.iter().position(|e| e.2 == edges[i].2).unwrap();
            edges[j] = edges[i];
            j
        } else {
            writeln!(out, "NO").ok();
            continue;
        };
        dsu.clear();
        for &(u, v, _) in edges.iter().take(k) {
            dsu.unite(u, v);
        }
        let ans = if dsu.unite(edges[k].0, edges[k].1) {
            "YES"
        } else {
            "NO"
        };
        writeln!(out, "{ans}").ok();
    }
}
