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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let blocks = sc.raw().as_bytes();
    let mut dp = vec![0; n];
    for (i, block) in blocks.iter().enumerate().skip(1) {
        let mut mn = usize::MAX;
        let prev = match *block {
            b'O' => b'B',
            b'J' => b'O',
            _ => b'J',
        };
        for j in 0..i {
            if blocks[j] == prev && dp[j] != usize::MAX {
                mn = mn.min(dp[j] + (i - j) * (i - j));
            }
        }
        dp[i] = mn;
    }
    writeln!(bw, "{}", dp[n - 1] as isize).ok();
}
