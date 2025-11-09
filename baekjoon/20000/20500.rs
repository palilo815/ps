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
    const M: u32 = 1_000_000_007;
    let n = sc.read::<usize>();
    let mut dp = vec![[0; 3]; n];
    dp[0][0] = 1;
    for i in 1..n {
        dp[i][0] = (dp[i - 1][2] + dp[i - 1][1]) % M;
        dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % M;
        dp[i][2] = (dp[i - 1][1] + dp[i - 1][0]) % M;
    }
    writeln!(bw, "{}", dp[n - 1][1]).ok();
}
