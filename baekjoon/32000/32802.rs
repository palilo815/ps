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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let events = (0..n)
        .map(|_| match sc.raw().bytes().next() {
            Some(b'C') => (sc.read::<i32>(), sc.read::<i32>(), sc.read::<i32>()),
            _ => (sc.read::<i32>(), -sc.read::<i32>(), -sc.read::<i32>()),
        })
        .collect::<Vec<_>>();
    let k = sc.read::<i32>();
    let (c, g) = events
        .into_iter()
        .filter(|e| e.0 <= k)
        .fold((0, 0), |acc, e| (acc.0 + e.1 as i64, acc.1 + e.2 as i64));
    writeln!(bw, "{c} {g}").ok();
}
