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
    const N: usize = 100_000;
    let mut y_val = [0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        for _ in 0..n {
            y_val[sc.read::<usize>() - 1] = sc.read::<u32>();
        }
        let ans = y_val
            .iter()
            .take(n)
            .fold((0, u32::MAX), |acc, &x| if x > acc.1 { acc } else { (acc.0 + 1, x) })
            .0;
        writeln!(bw, "{ans}").ok();
    }
}
