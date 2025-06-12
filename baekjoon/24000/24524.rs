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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let s = sc.read_bytes();
    let t = sc.read_bytes();
    let mut ord = [usize::MAX; 26];
    let mut dp = vec![0; t.len() + 1];
    for (i, x) in t.into_iter().enumerate() {
        ord[(x - b'a') as usize] = i;
    }
    dp[0] = u32::MAX;
    for x in s {
        let x = (x - b'a') as usize;
        if ord[x] == usize::MAX {
            continue;
        }
        if dp[ord[x]] != 0 {
            dp[ord[x]] -= 1;
            dp[ord[x] + 1] += 1;
        }
    }
    writeln!(bw, "{}", dp.last().unwrap()).ok();
}
