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
    let mut cnt = [0_u64; 4];
    for c in s.bytes() {
        match c {
            b'A' => cnt[0] += 1,
            b'C' => cnt[1] += 1,
            b'G' => cnt[2] += 1,
            _ => cnt[3] += 1,
        }
    }
    let ans = cnt.into_iter().fold(1, |prod, c| prod * c % 1_000_000_007);
    writeln!(bw, "{ans}").ok();
}
