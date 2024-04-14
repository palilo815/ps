use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let a = sc.read_vec::<usize>(n);
    let mut dp = vec![0; n + 1];
    dp[0] = 1;
    const M: i32 = 1_000_000_007;
    for i in 0..n {
        if i + a[i] < n {
            dp[i + a[i] + 1] += dp[i];
            dp[i + a[i] + 1] %= M;
        }
        if i >= a[i] && a[i] != a[i - a[i]] {
            dp[i + 1] += dp[i - a[i]];
            dp[i + 1] %= M;
        }
    }
    writeln!(bw, "{}", dp[n]).ok();
}
