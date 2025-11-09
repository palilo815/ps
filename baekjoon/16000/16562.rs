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

struct DisjointSet {
    p: Box<[i32]>,
}

impl DisjointSet {
    fn new(n: usize) -> Self {
        Self { p: vec![-1; n].into() }
    }
    fn find(&mut self, u: usize) -> usize {
        if self.p[u] < 0 {
            u
        } else {
            let root = self.find(self.p[u] as usize);
            self.p[u] = root as i32;
            root
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
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<u32>();
    let mut a = sc.read_vec::<u32>(n);
    let mut dsu = DisjointSet::new(n);
    for _ in 0..m {
        let u = dsu.find(sc.read::<usize>() - 1);
        let v = dsu.find(sc.read::<usize>() - 1);
        dsu.unite(u, v);
        let mn = a[u].min(a[v]);
        a[u] = mn;
        a[v] = mn;
    }
    let need = (0..n).filter(|&i| dsu.p[i] < 0).map(|i| a[i]).sum::<u32>();
    if need > k {
        writeln!(bw, "Oh no").ok();
    } else {
        writeln!(bw, "{need}").ok();
    }
}
