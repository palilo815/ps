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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u32>()))
        .collect::<Vec<_>>();
    edges.sort_unstable_by(|l, r| l.2.cmp(&r.2));
    let mut par = vec![-1; n];
    let mut tem = vec![(u32::MAX, -1); n];
    for (mut u, mut v, w) in edges {
        while par[u] >= 0 {
            u = par[u] as usize;
        }
        while par[v] >= 0 {
            v = par[v] as usize;
        }
        if u == v {
            continue;
        }
        if par[u] > par[v] {
            std::mem::swap(&mut u, &mut v);
        }
        par[u] += par[v];
        par[v] = u as i32;
        tem[v] = (w, -par[u]);
    }
    let q = sc.read::<usize>();
    for _ in 0..q {
        let mut u = sc.read::<usize>() - 1;
        let mut v = sc.read::<usize>() - 1;
        let mut ans = (u32::MAX, -1);
        while u != v {
            if tem[u] > tem[v] {
                std::mem::swap(&mut u, &mut v);
            }
            if par[u] < 0 {
                writeln!(bw, "-1").ok();
                break;
            }
            ans = tem[u];
            u = par[u] as usize;
        }
        if u == v {
            writeln!(bw, "{} {}", ans.0, ans.1).ok();
        }
    }
}
