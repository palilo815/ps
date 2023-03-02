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
    const INF: i32 = 0x3f3f3f3f;
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let d = sc.read_vec::<i32>(n);
    let mut dp = vec![INF; n + 1];
    dp[0] = 0;
    for _ in 0..m {
        let c = sc.read::<i32>();
        for i in (0..n).rev() {
            dp[i + 1] = dp[i + 1].min(dp[i] + d[i] * c);
        }
    }
    writeln!(out, "{}", dp[n]).ok();
}
