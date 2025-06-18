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
    loop {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        if n == 0 {
            break;
        }
        let k = m / n;
        let ans = (0..n).fold(0, |acc, _| acc + k.min(sc.read::<usize>()));
        writeln!(bw, "{ans}").ok();
    }
}
