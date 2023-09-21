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
    fn num_components(&self) -> usize {
        self.p.iter().filter(|x| x.is_negative()).count()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut dsu = DisjointSet::new(n);
    let mut edges = (0..m)
        .map(|_| {
            (
                sc.read::<usize>() - 1,
                sc.read::<usize>() - 1,
                sc.read::<u32>(),
                sc.read::<u32>(),
            )
        })
        .collect::<Vec<_>>();
    edges.sort_unstable_by(|l, r| l.2.cmp(&r.2).then(l.3.cmp(&r.3)));
    let mut count = [0; 10];
    let mut cost = 0;
    for (u, v, c, w) in edges {
        if dsu.unite(u, v) {
            count[c as usize] += 1;
            cost += w as u64;
        }
    }
    if dsu.num_components() != 1 {
        writeln!(out, "-1").ok();
        return;
    }
    for (i, c) in count.into_iter().enumerate() {
        (0..c).for_each(|_| {
            write!(out, "{i}").ok();
        })
    }
    writeln!(out, " {cost}").ok();
}
