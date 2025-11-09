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
    fn next(&mut self) -> Option<&'static str> {
        self.it.next()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.next().unwrap().parse::<usize>().unwrap();
    let k = sc.next().unwrap().parse::<usize>().unwrap();
    let mut ban = vec![false; n + 1];
    while let Some(s) = sc.next() {
        let i = s.parse::<usize>().unwrap();
        ban[i] = true;
    }
    let mut dp = vec![0; n + 1];
    for i in (0..=n).rev() {
        if ban[i] {
            continue;
        }
        if let Some(best) = (i + 1..=n).take(k).filter_map(|j| if ban[j] { None } else { Some(dp[j]) }).min() {
            ban[i] = true;
            dp[i] = best + 1;
        } else {
            dp[i] = dp[i + 1..].iter().take(k).max().unwrap_or(&0) + 1;
        }
    }
    writeln!(bw, "{}", dp[0] - 1).ok();
}
