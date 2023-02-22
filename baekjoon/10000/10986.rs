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
    let mut dp = vec![0; m];
    dp[0] = 1;
    let mut acc = 0;
    for _ in 0..n {
        acc = (acc + sc.read::<usize>()) % m;
        dp[acc] += 1;
    }
    let ans = dp.into_iter().fold(0u64, |acc, x| acc + x * (x - 1) / 2);
    writeln!(out, "{ans}").ok();
}
