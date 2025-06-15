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
        let m = sc.read::<f64>();
        let a = sc.read::<f64>();
        let b = sc.read::<f64>();
        if m == 0.0 {
            break;
        }
        let sec = 3600.0 * m * (b - a) / a / b;
        let sec = sec.round() as i64;
        writeln!(bw, "{}:{:02}:{:02}", sec / 3600, sec / 60 % 60, sec % 60).ok();
    }
}
