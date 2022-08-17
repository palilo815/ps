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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
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
    let _ = sc.read::<usize>();
    let mut dp = [0_u64; 4];
    for x in sc.raw().bytes() {
        match x {
            b'D' => dp[0] += 1,
            b'K' => dp[1] += dp[0],
            b'S' => dp[2] += dp[1],
            b'H' => dp[3] += dp[2],
            _ => (),
        }
    }
    writeln!(out, "{}", dp[3]).ok();
}
