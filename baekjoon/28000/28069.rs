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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let k = sc.read::<u32>();
    let mut dp = vec![u32::MAX; n + 1];
    dp[0] = 0;
    for i in 0..n {
        dp[i + 1] = dp[i + 1].min(dp[i] + 1);
        let j = i + i / 2;
        if j <= n {
            dp[j] = dp[j].min(dp[i] + 1);
        }
    }
    let ans = if dp[n] > k { "water" } else { "minigimbob" };
    writeln!(out, "{ans}").ok();
}
