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

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
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
    fn unite(&mut self, u: usize, v: usize) {
        let mut u = self.find(u);
        let mut v = self.find(v);
        if u == v {
            return;
        }
        if self.p[u] > self.p[v] {
            std::mem::swap(&mut u, &mut v);
        }
        self.p[u] += self.p[v];
        self.p[v] = u as i32;
    }
    fn size_of(&mut self, u: usize) -> usize {
        let root = self.find(u);
        (-self.p[root]) as usize
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let mut adj = vec![vec![]; n + 1];
    for _ in 1..n {
        let u = sc.read::<usize>();
        let v = sc.read::<usize>();
        adj[u].push(v);
        adj[v].push(u);
    }
    let par = {
        let mut par = vec![usize::MAX; n + 1];
        par[1] = 0;
        let mut stack = vec![1];
        for _ in 0..n {
            let u = stack.pop().unwrap();
            for &v in adj[u].iter() {
                if par[v] == usize::MAX {
                    par[v] = u;
                    stack.push(v);
                }
            }
        }
        par
    };
    let mut s = vec![0; n];
    let mut live = vec![false; n + 1];
    let mut dsu = DisjointSet::new(n + 1);
    let q = sc.read::<usize>();
    for _ in 0..q {
        let k = sc.read::<usize>();
        for x in s.iter_mut().take(k) {
            *x = sc.read::<usize>();
        }
        s.iter().take(k).for_each(|&x| live[x] = true);
        s.iter()
            .take(k)
            .filter(|&&x| live[par[x]])
            .for_each(|&x| dsu.unite(x, par[x]));
        let ans = s
            .iter()
            .take(k)
            .filter(|&&x| !live[par[x]])
            .fold(0, |acc, &x| {
                let sz = dsu.size_of(x);
                acc + sz * (sz - 1)
            })
            >> 1;
        writeln!(out, "{}", ans).ok();
        s.iter().take(k).for_each(|&x| {
            dsu.p[x] = -1;
            live[x] = false;
        });
    }
}
