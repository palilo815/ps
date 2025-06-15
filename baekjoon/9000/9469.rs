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
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let d = sc.read::<f64>();
        let a = sc.read::<f64>();
        let b = sc.read::<f64>();
        let f = sc.read::<f64>();
        writeln!(bw, "{} {:.8}", n, d / (a + b) * f).ok();
    }
}
