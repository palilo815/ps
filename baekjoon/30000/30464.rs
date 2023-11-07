use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
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
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let a = sc.read_vec::<usize>(n);
    let mut dp = vec![-1; n];
    dp[0] = 0;
    for i in 0..n - 1 {
        if dp[i] != -1 && i + a[i] < n {
            dp[i + a[i]] = dp[i + a[i]].max(dp[i] + 1);
        }
    }
    for i in (0..n - 1).rev() {
        if dp[i] != -1 && i >= a[i] {
            dp[i - a[i]] = dp[i - a[i]].max(dp[i] + 1);
        }
    }
    for i in 0..n - 1 {
        if dp[i] != -1 && i + a[i] < n {
            dp[i + a[i]] = dp[i + a[i]].max(dp[i] + 1);
        }
    }
    writeln!(out, "{}", dp[n - 1]).ok();
}
