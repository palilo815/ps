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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.raw().bytes().filter(|&x| x == b'1').count();
    let m = sc.raw().bytes().filter(|&x| x == b'1').count();
    writeln!(bw, "{}", if (n + (n & 1)) >= m { "VICTORY" } else { "DEFEAT" }).ok();
}
