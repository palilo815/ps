use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read_chars(&mut self) -> Vec<char> {
        self.it.next().unwrap().chars().collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let s = sc.read_chars();
    let t = sc.read_chars();
    let mut dp = vec![0; t.len() + 1];
    for a in s {
        let mut prv = 0;
        for (i, &b) in t.iter().enumerate() {
            let tmp = dp[i + 1];
            dp[i + 1] = if a == b { prv + 1 } else { dp[i + 1].max(dp[i]) };
            prv = tmp;
        }
    }
    writeln!(out, "{}", dp.last().unwrap()).ok();
}
