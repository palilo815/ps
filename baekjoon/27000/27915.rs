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
    let mut p = vec![0; n];
    for p in p.iter_mut().skip(1) {
        *p = sc.read::<usize>() - 1;
    }
    let mut dp = vec![(0, 0); n];
    for (i, p) in p.into_iter().enumerate().skip(1).rev() {
        if dp[i].1 == 0 {
            dp[i].0 += 1;
        } else {
            dp[i].1 -= 1;
        }
        dp[p].0 += dp[i].1;
        dp[p].1 += dp[i].0;
    }
    let n = n as i32;
    let (mut x, mut y) = dp[0];
    if y == 0 {
        x += 1;
    } else {
        y -= 1;
    }
    writeln!(out, "{}", (n - x - y) / 2 + x.max(y)).ok();
}
