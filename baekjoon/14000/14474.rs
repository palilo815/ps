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
    let m = sc.read::<usize>();
    let mut dp = sc.read_vec::<i32>(n * m);
    let mut loc = vec![0; n * m];
    for (i, &h) in dp.iter().enumerate() {
        loc[h as usize - 1] = i;
    }
    for (h, &i) in loc.iter().enumerate() {
        dp[i] = if (i < m || dp[i - m] > dp[i])
            && (i % m == 0 || dp[i - 1] > dp[i])
            && ((i + 1) % m == 0 || dp[i + 1] > dp[i])
            && (i + m >= n * m || dp[i + m] > dp[i])
        {
            h as i32
        } else {
            -1
        };
    }
    let dup = (n * m) as i32;
    let mut ans = 0;
    for i in loc.into_iter() {
        if i >= m && dp[i - m] != -1 {
            dp[i] = if dp[i] == -1 || dp[i] == dp[i - m] {
                dp[i - m]
            } else {
                dup
            };
        }
        if i % m != 0 && dp[i - 1] != -1 {
            dp[i] = if dp[i] == -1 || dp[i] == dp[i - 1] {
                dp[i - 1]
            } else {
                dup
            };
        }
        if (i + 1) % m != 0 && dp[i + 1] != -1 {
            dp[i] = if dp[i] == -1 || dp[i] == dp[i + 1] {
                dp[i + 1]
            } else {
                dup
            };
        }
        if i + m < n * m && dp[i + m] != -1 {
            dp[i] = if dp[i] == -1 || dp[i] == dp[i + m] {
                dp[i + m]
            } else {
                dup
            };
        }
        ans += (dp[i] == dup) as u32;
    }
    writeln!(out, "{ans}").ok();
}
