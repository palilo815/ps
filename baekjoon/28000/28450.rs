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
    let m = sc.read::<usize>();
    let mut dp = vec![0; m + 1];
    for i in 0..m {
        dp[i + 1] = dp[i] + sc.read::<u64>();
    }
    dp[0] = u64::MAX;
    for _ in 1..n {
        for i in 0..m {
            dp[i + 1] = dp[i].min(dp[i + 1]) + sc.read::<u64>();
        }
    }
    let h = sc.read::<u64>();
    if dp[m] > h {
        writeln!(out, "NO").ok();
    } else {
        writeln!(out, "YES").ok();
        writeln!(out, "{}", dp[m]).ok();
    }
}
