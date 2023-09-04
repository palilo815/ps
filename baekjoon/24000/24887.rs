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
    let m = sc.read::<u32>();
    let w = sc.read_vec::<u32>(n);
    if *w.iter().max().unwrap() >= m {
        writeln!(out, "Free!").ok();
        return;
    }
    if w.iter().fold(0, |acc, &x| acc + x as u64) < m as u64 {
        writeln!(out, "-1").ok();
        return;
    }
    let parametric = |mut lo, mut hi| {
        let mut dp = vec![0; n];
        let mut f = |mid| -> bool {
            let mut prev_best = 0;
            for i in 0..n {
                if i > mid {
                    prev_best = prev_best.max(dp[i - mid - 1]);
                }
                dp[i] = prev_best + w[i];
                if dp[i] >= m {
                    return true;
                }
            }
            false
        };
        // last true
        while lo != hi {
            let mid = hi - (hi - lo) / 2;
            if f(mid) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        lo
    };
    let ans = parametric(0, n - 1) as isize;
    writeln!(out, "{}", ans).ok();
}
