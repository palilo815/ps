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
    let a = sc.read_vec::<i32>(n);
    let total = a.iter().sum::<i32>();
    let mut dp = vec![0; n + 1];
    for i in 0..n {
        dp[i + 1] = dp[i] + if i & 1 == 0 { a[i] } else { -a[i] };
    }
    let mut best = i32::MIN;
    for i in 0..n {
        let diff = dp[i] + dp[i] - dp[n - 1] + if i & 1 == 0 { a[n - 1] } else { -a[n - 1] };
        best = best.max((diff + total) / 2);
    }
    writeln!(bw, "{best}").ok();
}
