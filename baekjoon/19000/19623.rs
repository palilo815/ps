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
    let mut a = (0..n).map(|_| (sc.read::<u32>(), sc.read::<u32>(), sc.read::<u32>())).collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    let mut dp = vec![0; n + 1];
    for i in 0..n {
        let cur = dp[i];
        dp[i + 1] = dp[i + 1].max(cur);
        let j = i + 1 + a[i + 1..].partition_point(|o| o.0 < a[i].1);
        dp[j] = dp[j].max(cur + a[i].2);
    }
    writeln!(bw, "{}", dp[n]).ok();
}
