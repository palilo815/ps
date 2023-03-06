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
    let a = sc.read_vec::<u32>(n);
    let mut candi = Vec::with_capacity(n * (n + 1) / 2);
    (0..n).for_each(|i| {
        candi.extend(a.iter().skip(i).scan(0, |acc, x| {
            *acc += x;
            Some(*acc)
        }));
    });
    candi.sort_unstable();
    candi.dedup();
    let mut dp = vec![0; n + 1];
    let mut best = u32::MAX;
    for mn in candi.into_iter() {
        dp[1..].fill(u32::MAX);
        for i in 0..n {
            if dp[i] == u32::MAX {
                continue;
            }
            let mut acc = 0;
            for j in i..if i == 0 { n - 1 } else { n } {
                acc += a[j];
                if acc >= mn {
                    dp[j + 1] = dp[j + 1].min(dp[i].max(acc));
                }
            }
        }
        best = best.min(dp[n] - mn);
    }
    writeln!(out, "{best}").ok();
}
