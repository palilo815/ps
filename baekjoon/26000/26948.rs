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
    const N: usize = 25;
    let mut dp = [0; N];
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    for i in 3..N {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }
    let n = sc.read::<usize>();
    writeln!(bw, "{}", dp[n]).ok();
}
