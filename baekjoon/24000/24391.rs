use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
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

struct DisjointSet {
    p: Vec<i32>,
}

#[allow(dead_code)]
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
    fn same(&mut self, u: usize, v: usize) -> bool {
        self.find(u) == self.find(v)
    }
    fn size_of(&mut self, u: usize) -> usize {
        let root = self.find(u);
        (-self.p[root]) as usize
    }
    fn num_components(&self) -> usize {
        self.p.iter().filter(|x| x.is_negative()).count()
    }
    fn iter_roots(&self) -> impl Iterator<Item = usize> + '_ {
        self.p
            .iter()
            .enumerate()
            .filter_map(|(i, x)| match x.is_negative() {
                true => Some(i),
                false => None,
            })
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let mut dsu = DisjointSet::new(n);
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        dsu.unite(u, v);
    }
    let mut ans = 0;
    let mut u = sc.next::<usize>() - 1;
    for _ in 1..n {
        let v = sc.next::<usize>() - 1;
        ans += !dsu.same(std::mem::replace(&mut u, v), v) as u32;
    }
    writeln!(out, "{}", ans).ok();
}
