use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
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
    if n == 1 {
        writeln!(out, "0").ok();
        return;
    }
    let a = sc.read_vec::<u32>(n);
    let mut dp = vec![0; n + 1];
    const INF: u32 = 0x3f3f3f3f;
    dp[0] = INF;
    dp[2] = INF + (a[0] ^ a[1]).count_ones();
    for i in 2..n {
        let take2 = (a[i] ^ a[i - 1]).count_ones();
        let take3 = (a[i] ^ a[i - 1] ^ a[i - 2]).count_ones();
        dp[i + 1] = (dp[i - 1] + take2).max(dp[i - 2] + take3);
    }
    writeln!(out, "{}", dp[n] - INF).ok();
}
