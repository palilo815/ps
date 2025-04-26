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
    let mut s = sc.read_bytes();
    s.dedup();
    if s.len() > 3 {
        s.truncate(if s.len() % 2 == 0 { 2 } else { 3 });
    }
    writeln!(bw, "{}", String::from_utf8(s).unwrap()).ok();
}
