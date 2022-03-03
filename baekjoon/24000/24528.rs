use std::io::Write;

mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let mut dp = [0; 26];
    const MOD: u64 = 998_244_353;
    for _ in 0..n {
        let c = sc.next::<char>() as usize - 'a' as usize;
        let v = sc.next::<u64>();
        let other = (dp.iter().sum::<u64>() - dp[c]) % MOD;
        dp[c] += (other + 1) * v;
        dp[c] %= MOD;
    }
    writeln!(out, "{}", dp.iter().sum::<u64>() % MOD).ok();
}
