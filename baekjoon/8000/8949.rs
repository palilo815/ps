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
    let mut a = sc.read::<u32>();
    let mut b = sc.read::<u32>();
    let mut stack = vec![];
    while a | b != 0 {
        stack.push(a % 10 + b % 10);
        a /= 10;
        b /= 10;
    }
    for x in stack.into_iter().rev() {
        write!(bw, "{x}").ok();
    }
}
