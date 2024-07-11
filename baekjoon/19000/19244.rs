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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 500;
    let mut dp = [[0; N + 1]; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let s = sc.raw().as_bytes();
        let n = s.len();
        for (i, dp) in dp.iter_mut().take(n).enumerate() {
            dp[i + 2..n + 1].fill(0);
        }
        for k in 2..=n {
            for i in 0..=n - k {
                let mut best = dp[i + 1][i + k].max(dp[i][i + k - 1]);
                if matches!(
                    (s[i], s[i + k - 1]),
                    (b'*', b'*')
                        | (b'(', b')')
                        | (b'{', b'}')
                        | (b'[', b']')
                        | (b'(', b'*')
                        | (b'{', b'*')
                        | (b'[', b'*')
                        | (b'*', b')')
                        | (b'*', b'}')
                        | (b'*', b']')
                ) {
                    best = best.max(dp[i + 1][i + k - 1] + 2);
                }
                for j in i + 1..i + k {
                    best = best.max(dp[i][j] + dp[j][i + k]);
                }
                dp[i][i + k] = best;
            }
        }
        writeln!(bw, "{}", n as i32 - dp[0][n]).ok();
    }
}
