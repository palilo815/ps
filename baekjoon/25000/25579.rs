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
    fn size_of(&mut self, u: usize) -> i64 {
        let root = self.find(u);
        (-self.p[root]) as i64
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let mut b = sc.read_vec::<i64>(n);
    let p = (0..n).map(|_| sc.read::<usize>() - 1).collect::<Vec<_>>();
    let mut dsu = DisjointSet::new(n);
    let mut check = vec![false; n];
    let mut ans = 0;
    let mut cur = 0;
    for p in p.into_iter().skip(1).rev() {
        check[p] = true;
        if p != 0 && check[p - 1] {
            let q = dsu.find(p - 1);
            cur -= dsu.size_of(q) * b[q];
            b[p] += b[q];
            dsu.p[p] += dsu.p[q];
            dsu.p[q] = p as i32;
        }
        if p + 1 != n && check[p + 1] {
            let q = dsu.find(p + 1);
            cur -= dsu.size_of(q) * b[q];
            b[p] += b[q];
            dsu.p[p] += dsu.p[q];
            dsu.p[q] = p as i32;
        }
        cur += dsu.size_of(p) * b[p];
        ans = ans.max(cur);
    }
    writeln!(out, "{ans}").ok();
}
