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
    let k = sc.read::<usize>();
    let h = sc.read::<u64>();
    let patterns = (0..k)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<usize>() - 1, sc.read::<u64>()))
        .collect::<Vec<_>>();
    const INF: u64 = 0x3f3f3f3f3f3f3f3f;
    let mut dp = vec![INF; n];
    dp[n - 1] = 0;
    for (i, j, x) in patterns.into_iter().rev() {
        let ci = dp[i];
        let cj = dp[j];
        dp[i] = cj.min(ci + x);
        dp[j] = ci.min(cj + x);
    }
    let res2 = dp[n - 1] * (h - 1);
    let res1 = dp.into_iter().filter(|&x| x != INF).max().unwrap();
    writeln!(bw, "{}", res1 + res2).ok();
}
