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
    const INF: i32 = 0x3f3f3f3f;
    let mut dp = vec![INF; x + 1];
    dp[0] = 0;
    for _ in 0..n {
        let coin = sc.read::<usize>();
        for i in coin..=x {
            dp[i] = dp[i].min(dp[i - coin] + 1);
        }
    }
    writeln!(out, "{}", if dp[x] == INF { -1 } else { dp[x] }).ok();
}
