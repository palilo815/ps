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
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<i32>();
    let (mn, mx) = (0..n).fold((i32::MAX, i32::MIN), |(mn, mx), _| {
        let x = sc.read::<i32>();
        (mn.min(x), mx.max(x))
    });
    writeln!(bw, "{mn} {mx}").ok();
}
