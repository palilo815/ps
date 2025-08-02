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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let s = sc.raw().as_bytes();
    let mut ans = 0;
    for i in 1..=s.len() {
        let set = s.windows(i).map(|s| s.to_vec()).collect::<std::collections::HashSet<_>>();
        ans += set.len();
    }
    writeln!(bw, "{ans}").ok();
}
