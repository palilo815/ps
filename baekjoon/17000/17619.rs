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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let q = sc.read::<usize>();
    let mut lines = (0..n)
        .map(|i| {
            let line = (sc.read::<i32>(), sc.read::<i32>(), i);
            sc.raw();
            line
        })
        .collect::<Vec<_>>();
    lines.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    let mut gid = vec![0; n];
    let mut prv = -1;
    let mut group = -1;
    for (x1, x2, i) in lines {
        if prv < x1 {
            group += 1;
        }
        gid[i] = group;
        prv = prv.max(x2);
    }
    for _ in 0..q {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        writeln!(bw, "{}", (gid[u] == gid[v]) as i32).ok();
    }
}
