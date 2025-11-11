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
    const N: usize = 10_000;
    const MOD: usize = 1_000_000_007;
    let mut dp = vec![[[0; 7]; 7]; N + 1];
    dp[1][0][0] = 1;
    dp[1][1][1] = 2;
    dp[1][2][2] = 2;
    dp[1][3][3] = 1;
    dp[1][4][4] = 1;
    dp[1][5][5] = 1;
    dp[1][6][6] = 1;
    for i in 1..N {
        for j in 0..7 {
            for k in 0..7 {
                let cur = dp[i][j][k];
                if cur == 0 {
                    continue;
                }
                for digit in 0..10 {
                    let j = (j + digit) % 7;
                    let k = (k * digit) % 7;
                    dp[i + 1][j][k] = (dp[i + 1][j][k] + cur) % MOD;
                }
            }
        }
    }
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        writeln!(bw, "{}", dp[n][0][0]).ok();
    }
}
