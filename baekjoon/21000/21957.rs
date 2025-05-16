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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let a = sc.read_vec::<u32>(n);
    let mut dp = vec![vec![0; n]; n];
    for i in 0..n {
        dp[i][i] = a[i];
    }
    for len in 1..n {
        for (i, j) in (0..).zip(len..n) {
            dp[i][j] = (i..j).map(|k| (dp[i][k] + dp[k + 1][j]) / 2).max().unwrap();
        }
    }
    writeln!(bw, "{}", dp[0][n - 1]).ok();
}
