use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
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
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let win = sc.read_vec::<i32>(n);
    let m = sc.read::<usize>();
    let lose = sc.read_vec::<i32>(m);
    let k = sc.read::<i32>();
    let mut dp = vec![0; n + 1];
    for i in 0..n {
        dp[i + 1] = dp[i] + win[i];
    }
    let mut tp = vec![0; n + 1];
    for l in lose {
        std::mem::swap(&mut dp, &mut tp);
        dp[0] = tp[0] - if tp[0] % k == 0 { l } else { l.min(tp[0].rem_euclid(k)) };
        for i in 1..n + 1 {
            dp[i] = (dp[i - 1] + win[i - 1]).max(tp[i] - if tp[i] % k == 0 { l } else { l.min(tp[i].rem_euclid(k)) });
        }
    }
    writeln!(bw, "{}", dp[n]).ok();
}
