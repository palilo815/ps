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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let _ = sc.read::<usize>();
    let s = sc.read_bytes();
    let q = sc.read::<usize>();
    let mut map = std::collections::HashMap::new();
    let mut dsu = DisjointSet::new(q);
    for i in 0..q {
        let pos = (sc.read::<i32>(), sc.read::<i32>());
        if let Some(j) = map.insert(pos, i) {
            dsu.unite(i, j);
        }
    }
    let mut wall = (0, 0);
    for c in s.into_iter() {
        let delta = match c {
            b'R' => (-1, 0),
            b'L' => (1, 0),
            b'U' => (0, -1),
            _ => (0, 1),
        };
        wall.0 += delta.0;
        wall.1 += delta.1;
        if let Some(i) = map.remove(&wall) {
            if let Some(j) = map.insert((wall.0 + delta.0, wall.1 + delta.1), i) {
                dsu.unite(i, j);
            }
        }
    }
    let mut ans = vec![(0, 0); q];
    for (pos, i) in map.into_iter() {
        ans[dsu.find(i)] = (pos.0 - wall.0, pos.1 - wall.1);
    }
    for i in 0..q {
        let (x, y) = ans[dsu.find(i)];
        writeln!(out, "{x} {y}").ok();
    }
}
