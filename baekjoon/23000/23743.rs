macro_rules! input {
    (source = $s:expr, $($r:tt)*) => {
        let mut iter = $s.split_whitespace();
        input_inner!{iter, $($r)*}
    };
    ($($r:tt)*) => {
        let s = {
            use std::io::Read;
            let mut s = String::new();
            std::io::stdin().read_to_string(&mut s).unwrap();
            s
        };
        let mut iter = s.split_whitespace();
        input_inner!{iter, $($r)*}
    };
}

macro_rules! input_inner {
    ($iter:expr) => {};
    ($iter:expr, ) => {};
    ($iter:expr, $var:ident : $t:tt $($r:tt)*) => {
        let $var = read_value!($iter, $t);
        input_inner!{$iter $($r)*}
    };
}

macro_rules! read_value {
    ($iter:expr, ( $($t:tt),* )) => {
        ( $(read_value!($iter, $t)),* )
    };
    ($iter:expr, [ $t:tt ; $len:expr ]) => {
        (0..$len).map(|_| read_value!($iter, $t)).collect::<Vec<_>>()
    };
    ($iter:expr, chars) => {
        read_value!($iter, String).chars().collect::<Vec<char>>()
    };
    ($iter:expr, bytes) => {
        read_value!($iter, String).bytes().collect::<Vec<u8>>()
    };
    ($iter:expr, usize1) => {
        read_value!($iter, usize) - 1
    };
    ($iter:expr, $t:ty) => {
        $iter.next().unwrap().parse::<$t>().expect("Parse error")
    };
}

use std::io::Write;

pub struct DisjointSet {
    p: Vec<i32>,
}

impl DisjointSet {
    pub fn new(n: usize) -> DisjointSet {
        DisjointSet { p: vec![-1; n] }
    }
    pub fn find(&mut self, mut u: usize) -> usize {
        assert!(u < self.p.len());
        while self.p[u] >= 0 {
            if self.p[self.p[u] as usize] >= 0 {
                self.p[u] = self.p[self.p[u] as usize];
            }
            u = self.p[u] as usize;
        }
        u
    }
    pub fn unite(&mut self, u: usize, v: usize) -> bool {
        assert!(u < self.p.len() && v < self.p.len());
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
    pub fn size(&mut self, u: usize) -> usize {
        assert!(u < self.p.len());
        let root = self.find(u);
        (-self.p[root]) as usize
    }
}

fn main() {
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    input! {
        n: usize,
        m: usize,
        edges: [(usize, usize, i32); m],
        t: [i32; n],
    }
    let mut edges = edges;
    edges.extend((0..n).map(|x| (0, x + 1, t[x])).collect::<Vec<_>>());
    edges.sort_unstable_by_key(|&x| x.2);
    let mut dsu = DisjointSet::new(n + 1);
    let mut ans = 0;
    for &(u, v, w) in edges.iter() {
        if dsu.unite(u, v) {
            ans += w;
        }
    }
    writeln!(out, "{}", ans).ok();
}
