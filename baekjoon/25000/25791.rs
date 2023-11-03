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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let l = sc.read::<usize>();
    let t = sc.read::<usize>();
    const INF: i32 = 0x3f3f3f3f;
    let mut dp = vec![INF; 3.max(l + 1)];
    dp[0] = 0;
    for _ in 0..t {
        let a1 = sc.read::<i32>();
        let a2 = sc.read::<i32>();
        let a3 = sc.read::<i32>();
        for i in (3..=l).rev() {
            dp[i] = std::cmp::min(dp[i].min(dp[i - 1] + a1), (dp[i - 2] + a2).min(dp[i - 3] + a3));
        }
        dp[2] = dp[2].min(dp[1] + a1).min(a2);
        dp[1] = dp[1].min(a1);
    }
    writeln!(out, "{}", dp[l]).ok();
}
