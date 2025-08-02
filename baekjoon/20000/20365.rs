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
    let _ = sc.raw();
    let s = sc.raw();
    let diff = s.as_bytes().windows(2).filter(|w| w[0] != w[1]).count();
    writeln!(bw, "{}", diff.div_ceil(2) + 1).ok();
}
