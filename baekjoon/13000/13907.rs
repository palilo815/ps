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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let s = sc.read::<usize>() - 1;
    let d = sc.read::<usize>() - 1;
    let edges = (0..m)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<usize>()))
        .collect::<Vec<_>>();
    const INF: usize = 0x3f3f3f3f3f3f3f3f;
    let mut best = vec![INF; n];
    let mut dp = vec![INF; n];
    let mut tp = vec![0; n];
    dp[s] = 0;
    for i in 1..n {
        std::mem::swap(&mut dp, &mut tp);
        dp.fill(INF);
        for &(u, v, w) in edges.iter() {
            dp[u] = dp[u].min(tp[v] + w);
            dp[v] = dp[v].min(tp[u] + w);
        }
        best[i] = dp[d];
    }
    writeln!(out, "{}", best.iter().min().unwrap()).ok();
    for _ in 0..k {
        let p = sc.read::<usize>();
        for (i, x) in best.iter_mut().enumerate() {
            *x += i * p;
        }
        writeln!(out, "{}", best.iter().min().unwrap()).ok();
    }
}
