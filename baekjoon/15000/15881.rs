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
    sc.raw();
    let mut ans = 0;
    let mut i = 0;
    for c in sc.raw().bytes() {
        match c {
            b'P' => i = if i == 1 { 2 } else { 0 },
            b'A' => i = if i == 2 { 3 } else { 0 },
            _ => {
                if i == 3 {
                    i = 0;
                    ans += 1;
                } else {
                    i = 1;
                }
            }
        }
    }
    writeln!(bw, "{ans}").ok();
}
