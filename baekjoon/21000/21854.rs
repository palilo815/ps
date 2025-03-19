use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const MOD: u64 = 1_000_000_007;
    let n = sc.read::<usize>();
    let mut ans = 0;
    for _ in 0..n {
        let mut k = sc.read::<i32>();
        let mut x = 2;
        let mut r = 1;
        while k != 0 {
            if k & 1 == 1 {
                r = r * x % MOD;
            }
            k >>= 1;
            x = x * x % MOD;
        }
        ans = (ans + r) % MOD;
    }
    writeln!(bw, "{ans}").ok();
}
