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
    let m = sc.read::<i32>();
    let a = sc.read_vec::<i32>(n);
    let c = sc.read_vec::<usize>(n);
    let mut dp = vec![-1; 10_001];
    dp[0] = 0;
    for (a, c) in a.into_iter().zip(c.into_iter()) {
        for i in (c..10_001).rev() {
            if dp[i - c] != -1 {
                dp[i] = dp[i].max(dp[i - c] + a);
            }
        }
    }
    let ans = dp.into_iter().position(|x| x >= m).unwrap();
    writeln!(out, "{ans}").ok();
}
