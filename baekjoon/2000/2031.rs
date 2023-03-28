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
    let _ = sc.read::<usize>();
    let n = sc.read::<usize>();
    let d = sc.read::<i32>();
    let k = sc.read::<u32>();
    let mut a = sc.read_vec::<i32>(n);
    a.sort_unstable();
    let prev = a
        .iter()
        .scan(0, |i, x| {
            while a[*i] < x - d + 1 {
                *i += 1;
            }
            Some(*i)
        })
        .collect::<Vec<_>>();
    let mut dp = vec![0; n + 1];
    let mut tp = vec![0; n + 1];
    for _ in 0..k {
        std::mem::swap(&mut dp, &mut tp);
        for i in 0..n {
            dp[i + 1] = dp[i].max(tp[prev[i]] + i + 1 - prev[i]);
        }
    }
    writeln!(out, "{}", dp[n]).ok();
}
