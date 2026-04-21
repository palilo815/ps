use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = Vec::new();
        stdin().lock().read_to_end(&mut buf).ok();
        let s = unsafe { std::str::from_utf8_unchecked(Box::leak(buf.into_boxed_slice())) };
        Self { it: s.split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let mut a = sc.read::<i64>();
    let mut b = sc.read::<i64>();
    if a > b {
        std::mem::swap(&mut a, &mut b);
    }
    writeln!(bw, "{}", (b - a - 1).max(0)).ok();
    for x in a + 1..b {
        write!(bw, "{x} ").ok();
    }
}
