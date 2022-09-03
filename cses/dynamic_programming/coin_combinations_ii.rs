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
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let x = sc.read::<usize>();
    let mut dp = vec![0; x + 1];
    dp[0] = 1;
    for _ in 0..n {
        let coin = sc.read::<usize>();
        for i in coin..=x {
            dp[i] += dp[i - coin];
            dp[i] %= 1_000_000_007;
        }
    }
    writeln!(out, "{}", dp[x]).ok();
}
