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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let a = sc.read_vec::<i32>(n);
    let b = sc.read::<i64>();
    let c = sc.read::<i64>();
    let ans = a
        .into_iter()
        .map(|a| a as i64)
        .map(|a| if a < b { 1 } else { (a - b + c - 1) / c + 1 })
        .sum::<i64>();
    writeln!(bw, "{ans}").ok();
}
