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
    let mut dp = Vec::with_capacity(n + 1);
    dp.push(0);
    for _ in 0..n {
        let x = sc.read::<i32>();
        let len = dp.len();
        for i in (0..len).rev() {
            if i == 0 || dp[i] >= x {
                if i + 1 == dp.len() {
                    dp.push(0);
                }
                dp[i + 1] = dp[i + 1].max(dp[i] + x);
            }
        }
    }
    writeln!(bw, "{}", dp.len() - 1).ok();
}
