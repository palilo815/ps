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
    let a1 = sc.read::<i32>();
    let mut h1 = sc.read::<i32>();
    let a2 = sc.read::<i32>();
    let mut h2 = sc.read::<i32>();
    while h1 > 0 && h2 > 0 {
        h1 -= a2;
        h2 -= a1;
    }
    let ans = match (h1 > 0, h2 > 0) {
        (false, false) => "DRAW",
        (true, false) => "PLAYER A",
        (false, true) => "PLAYER B",
        _ => unreachable!(),
    };
    writeln!(bw, "{ans}").ok();
}
