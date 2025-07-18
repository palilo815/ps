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
    let mut dp = vec![u32::MAX; n + 1];
    dp[1] = 0;
    for i in 1..n {
        let x = dp[i] + 1;
        if i * 2 <= n {
            dp[i * 2] = dp[i * 2].min(x);
        }
        if i * 3 <= n {
            dp[i * 3] = dp[i * 3].min(x);
        }
        dp[i + 1] = dp[i + 1].min(x);
    }
    writeln!(bw, "{}", dp[n]).ok();
}
