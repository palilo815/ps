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
    let n = sc.read::<usize>();
    let x = sc.read::<i32>();
    let mut prv = sc.read::<i32>();
    let mut best = i32::MAX;
    for _ in 1..n {
        let cur = sc.read::<i32>();
        best = best.min(prv + cur);
        prv = cur;
    }
    writeln!(bw, "{}", best * x).ok();
}

