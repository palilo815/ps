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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

struct DisjointSet {
    pub p: Box<[i32]>,
}

impl DisjointSet {
    fn new(n: usize) -> Self {
        Self {
            p: vec![-1; n].into_boxed_slice(),
        }
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
    let n = sc.read::<usize>();
    let mut rec = sc.read_vec::<usize>(2 * n);
    let mut values = rec.clone();
    values.sort_unstable();
    values.dedup();
    for x in rec.iter_mut() {
        *x = values.partition_point(|v| v < x);
    }
    let m = values.len();
    let mut dsu = DisjointSet::new(m);
    let mut cycle = vec![false; m];
    let mut ans = values.iter().sum::<usize>().wrapping_neg();
    for i in 0..n {
        let u = rec[i << 1];
        let v = rec[i << 1 | 1];
        ans += values[u] + values[v];
        if !dsu.unite(u, v) {
            cycle[u] = true;
        }
    }
    let mut max_vtx = vec![0; m];
    for (i, &x) in values.iter().enumerate() {
        let p = dsu.find(i);
        max_vtx[p] = max_vtx[p].max(x);
    }
    for i in 0..m {
        cycle[dsu.find(i)] |= cycle[i];
    }
    for i in 0..m {
        if !cycle[i] && dsu.p[i] < 0 {
            ans += max_vtx[i];
        }
    }
    writeln!(out, "{ans}").ok();
}
