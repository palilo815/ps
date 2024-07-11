use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
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
    const N: usize = 200;
    let mut dp = [true; N + 1];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let s = sc.raw().as_bytes();
        let n = s.len();
        let dp = &mut dp[..n + 1];
        dp[1..].fill(false);
        for i in 0..n {
            if !dp[i] {
                continue;
            }
            if i + 1 < n && s[i] == b'0' && s[i + 1] == b'1' {
                dp[i + 2] = true;
            }
            if i + 3 < n && s[i] == b'1' && s[i + 1] == b'0' && s[i + 2] == b'0' {
                let mut j = i + 3;
                while j != n && s[j] == b'0' {
                    j += 1;
                }
                while j != n && s[j] == b'1' {
                    j += 1;
                    dp[j] = true;
                }
            }
        }
        writeln!(bw, "{}", if dp[n] { "YES" } else { "NO" }).ok();
    }
}
