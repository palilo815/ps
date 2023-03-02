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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let _ = sc.read::<usize>();
    const MOD: i32 = 10007;
    let mut dp = [0; 8];
    dp[1] = 1;
    for c in sc.raw().bytes() {
        let need = match c {
            b'J' => 1,
            b'O' => 2,
            _ => 4,
        };
        let tp = dp;
        dp.fill(0);
        for i in (1..8).filter(|i| (i & need) != 0) {
            for j in (1..8).filter(|j| (i & j) != 0) {
                dp[i] += tp[j];
            }
        }
        dp.iter_mut().for_each(|x| *x %= MOD);
    }
    writeln!(out, "{}", dp.iter().sum::<i32>() % MOD).ok();
}
