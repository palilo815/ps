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
    const INF: u32 = 0x3f3f3f3f;
    let mut dp = vec![INF; n + 1];
    dp[n] = 0;
    for i in (1..=n).rev() {
        let mut num = i;
        while num != 0 {
            let d = num % 10;
            dp[i - d] = dp[i - d].min(dp[i] + 1);
            num /= 10;
        }
    }
    writeln!(out, "{}", dp[0]).ok();
}
