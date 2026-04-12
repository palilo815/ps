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
    let a = sc.read::<i32>();
    let b = sc.read::<i32>();
    let mut h = sc.read::<i32>();
    for i in 1.. {
        h -= a;
        if h <= 0 {
            writeln!(bw, "{i}").ok();
            return;
        }
        h += b;
    }
}
