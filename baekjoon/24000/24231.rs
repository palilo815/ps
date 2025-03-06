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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const MOD: i64 = 1_000_000_007;
    let s = sc.read_bytes();
    let n = s.len();
    let mut dp = vec![vec![0; n + 1]; n + 1];
    for (i, row) in dp.iter_mut().enumerate() {
        row[i] = 1;
    }
    for k in (2..=n).step_by(2) {
        for i in 0..=n - k {
            let mut acc = 0;
            for j in i + 1..i + k {
                if s[i] ^ s[j] == 1 {
                    acc = (acc + dp[i + 1][j] * dp[j + 1][i + k]) % MOD;
                }
            }
            dp[i][i + k] = acc;
        }
    }
    writeln!(bw, "{}", dp[0][n]).ok();
}
