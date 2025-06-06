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
    let ans = (0..n)
        .map(|_| sc.read::<i32>() + sc.read::<i32>() + sc.read::<i32>())
        .filter(|&x| x >= 512)
        .min()
        .unwrap_or(-1);
    writeln!(bw, "{ans}").ok();
}
