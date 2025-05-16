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
    let mut dp = vec![0; n];
    for i in 0..n {
        let t = sc.read::<u32>();
        let k = sc.read::<usize>();
        dp[i] = t + (0..k).map(|_| dp[sc.read::<usize>() - 1]).max().unwrap_or_default();
    }
    writeln!(bw, "{}", dp.into_iter().max().unwrap()).ok();
}
