use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a String) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

pub struct DisjointSet {
    p: Vec<i32>,
}

impl DisjointSet {
    pub fn new(n: usize) -> Self {
        Self { p: vec![-1; n] }
    }
    pub fn find(&mut self, u: usize) -> usize {
        if self.p[u] < 0 {
            u
        } else {
            let rt = self.find(self.p[u] as usize);
            self.p[u] = rt as i32;
            rt
        }
    }
    pub fn unite(&mut self, u: usize, v: usize) -> bool {
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
    pub fn same(&mut self, u: usize, v: usize) -> bool {
        self.find(u) == self.find(v)
    }
    pub fn size_of(&mut self, u: usize) -> usize {
        let root = self.find(u);
        (-self.p[root]) as usize
    }
    pub fn num_components(&self) -> usize {
        self.p.iter().filter(|x| x.is_negative()).count()
    }
}

trait ChMinMax {
        fn chmin(&mut self, x: Self) -> bool;
        fn chmax(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChMinMax for T {
    fn chmin(&mut self, x: Self) -> bool {
        *self > x && {
            *self = x;
            true
        }
    }
    fn chmax(&mut self, x: Self) -> bool {
        *self < x && {
            *self = x;
            true
        }
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let t = sc.next::<usize>();
    for _ in 0..t {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();
        let mut dsu = DisjointSet::new(n);
        for _ in 0..m {
            dsu.unite(sc.next::<usize>() - 1, sc.next::<usize>() - 1);
        }
        let s_root = dsu.find(0);
        let t_root = dsu.find(n - 1);
        if s_root == t_root {
            writeln!(out, "0").ok();
            continue;
        }
        let mut kids = vec![vec![]; n];
        for i in 0..n {
            kids[dsu.find(i)].push(i);
        }
        let s = &kids[s_root];
        let t = &kids[t_root];
        let mut ds = vec![0; n];
        let mut dt = vec![0; n];
        let mut i = 0;
        let mut j = 0;
        for k in 0..n {
            while i != s.len() && s[i] < k {
                i += 1;
            }
            while j != t.len() && t[j] < k {
                j += 1;
            }
            ds[k] = std::cmp::min(
                if i == 0 {
                    usize::MAX
                } else {
                    (k - s[i - 1]) * (k - s[i - 1])
                },
                if i == s.len() {
                    usize::MAX
                } else {
                    (k - s[i]) * (k - s[i])
                },
            );
            dt[k] = std::cmp::min(
                if j == 0 {
                    usize::MAX
                } else {
                    (k - t[j - 1]) * (k - t[j - 1])
                },
                if j == t.len() {
                    usize::MAX
                } else {
                    (k - t[j]) * (k - t[j])
                },
            );
        }
        let mut ans = usize::MAX;
        for i in 0..n {
            let r = dsu.find(i);
            if kids[r].is_empty() {
                continue;
            }
            let u = *kids[r].iter().min_by_key(|x| ds[**x]).unwrap();
            let v = *kids[r].iter().min_by_key(|x| dt[**x]).unwrap();
            ans.chmin(ds[u] + dt[v]);
            kids[r].clear();
        }
        writeln!(out, "{}", ans).ok();
    }
}
