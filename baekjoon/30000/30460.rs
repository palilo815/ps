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
    let n = sc.read::<usize>();
    let mut a = vec![0; n + 2];
    for x in a.iter_mut().take(n) {
        *x = sc.read::<i32>();
    }
    let n = n + 2;
    let mut dp = vec![0; n + 1];
    dp[1] = a[0];
    dp[2] = a[0] + a[1];
    for i in 2..n {
        let sum = a[i] + a[i - 1] + a[i - 2];
        dp[i + 1] = (dp[i] + a[i]).max(dp[i - 2] + sum * 2);
    }
    writeln!(out, "{}", dp[n]).ok();
}
