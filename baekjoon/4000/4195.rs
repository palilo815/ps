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
    fn read_array<const N: usize>(&mut self) -> [u8; N] {
        let s = self.it.next().unwrap();
        let mut a = [0; N];
        a[..s.len()].copy_from_slice(s.as_bytes());
        a
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
    fn size_of(&mut self, u: usize) -> usize {
        let root = self.find(u);
        (-self.p[root]) as usize
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const M: usize = 20;
    let mut map = std::collections::HashMap::new();
    let mut dsu = DisjointSet::new(200_000);
    let t = sc.read::<usize>();
    for _ in 0..t {
        map.clear();
        let n = sc.read::<usize>();
        let mut size = 0;
        for _ in 0..n {
            let u = sc.read_array::<M>();
            let v = sc.read_array::<M>();
            let u = *map.entry(u).or_insert_with(|| {
                let prv = size;
                size += 1;
                prv
            });
            let v = *map.entry(v).or_insert_with(|| {
                let prv = size;
                size += 1;
                prv
            });
            dsu.unite(u, v);
            writeln!(bw, "{}", dsu.size_of(u)).ok();
        }
        dsu.p[..size].fill(-1);
    }
}
