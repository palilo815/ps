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
    let mut ans = 0_u64;
    let mut acc = 0;
    let mut len = 0;
    for c in s.bytes() {
        if c == b'2' {
            len += 1;
            acc += len;
            ans += acc;
        } else {
            len = 0;
            acc = 0;
        }
    }
    writeln!(bw, "{ans}").ok();
}
