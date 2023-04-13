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
    let k = sc.read::<u64>();
    let a = sc.read_vec::<u32>(n);
    let mut dp = [0, 0];
    for a in a.into_iter() {
        let a = a as u64;
        let b = sc.read::<u64>();
        let prv = dp;
        dp[0] = (prv[0] + a).min(prv[1] + a + k);
        dp[1] = (prv[1] + b).min(prv[0] + b + k);
    }
    writeln!(out, "{}", dp[0].min(dp[1])).ok();
}
