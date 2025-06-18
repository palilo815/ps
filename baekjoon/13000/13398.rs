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
    let n = sc.read::<usize>();
    let mut dp1 = sc.read::<i32>();
    let mut dp2 = 0;
    let mut best1 = dp1;
    let mut best2 = dp2;
    for _ in 1..n {
        let x = sc.read::<i32>();
        dp2 = dp1.max(dp2 + x);
        dp1 = x.max(dp1 + x);
        best1 = best1.max(dp1);
        best2 = best2.max(dp2);
    }
    let best = best1.max(best2);
    writeln!(bw, "{}", if best == 0 { best1 } else { best }).ok();
}
