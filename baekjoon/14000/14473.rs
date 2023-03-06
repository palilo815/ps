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
    let mut pref = vec![[0; 20]; n + 1];
    for i in 0..n {
        pref[i + 1] = pref[i];
        pref[i + 1][sc.read::<usize>() - 1] += 1;
    }
    let mut dp = vec![u32::MAX; 1 << m];
    dp[0] = 0;
    for i in 0..dp.len() {
        let r = (0..20).fold(0, |acc, bit| {
            acc + if (i >> bit & 1) == 1 { pref[n][bit] } else { 0 }
        });
        for bit in (0..20).filter(|bit| (i >> bit & 1) == 1) {
            let l = r - pref[n][bit];
            let x = (r - l) - (pref[r as usize][bit] - pref[l as usize][bit]);
            dp[i] = dp[i].min(dp[i ^ (1 << bit)] + x);
        }
    }
    writeln!(out, "{}", dp.last().unwrap()).ok();
}
