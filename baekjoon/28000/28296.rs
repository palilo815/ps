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
    pub p: Vec<i32>,
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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut maps = (0..n)
        .map(|_| std::collections::HashMap::from([(sc.read::<usize>() - 1, 1)]))
        .collect::<Vec<_>>();
    let mut edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u64>()))
        .collect::<Vec<_>>();
    edges.sort_unstable_by(|l, r| r.2.cmp(&l.2));
    let mut dsu = DisjointSet::new(n);
    let mut ans = vec![0; k];
    for (u, v, w) in edges {
        let u = dsu.find(u);
        let v = dsu.find(v);
        if u != v {
            if maps[u].len() < maps[v].len() {
                maps.swap(u, v);
            }
            for (company, num) in std::mem::take(&mut maps[v]) {
                let entry = maps[u].entry(company).or_default();
                ans[company] += w * num * *entry;
                *entry += num;
            }
            dsu.p[u] += dsu.p[v];
            dsu.p[v] = u as i32;
        }
    }
    for x in ans {
        writeln!(out, "{x}").ok();
    }
}
