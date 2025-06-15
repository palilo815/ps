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
    const N: usize = 100;
    let mut dp = [0_u64; N + 1];
    dp[..5].copy_from_slice(&[0, 1, 1, 1, 2]);
    for i in 5..=N {
        dp[i] = dp[i - 5] + dp[i - 1];
    }
    let t = sc.read::<usize>();
    for _ in 0..t {
        writeln!(bw, "{}", dp[sc.read::<usize>()]).ok();
    }
}
