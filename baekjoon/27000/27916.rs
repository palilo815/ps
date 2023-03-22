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
    let q = sc.read::<usize>();
    let a = sc.read_vec::<i32>(n);
    let parametric = |mut lo, mut hi| {
        let mut dp = vec![false; n + 1];
        dp[0] = true;
        let mut f = |mid| -> bool {
            dp[1..].fill(false);
            let mut j = 0;
            for i in 0..n {
                if dp[i] {
                    j = j.max(i + m);
                    while j <= n && a[j - 1] <= a[i] + mid {
                        dp[j] = true;
                        j += 1;
                    }
                }
            }
            dp[n]
        };
        // first true
        while lo != hi {
            let mid = lo + (hi - lo) / 2;
            if f(mid) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        lo
    };
    let lim = parametric(0, 1_000_000_000);
    let ans = (0..q).map(|_| if sc.read::<i32>() < lim { '0' } else { '1' });
    writeln!(out, "{}", String::from_iter(ans)).ok();
}
