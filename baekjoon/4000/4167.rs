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
    const R: f64 = 6371009.;
    let t = sc.read::<usize>();
    for _ in 0..t {
        let x1 = sc.read::<f64>().to_radians();
        let y1 = sc.read::<f64>().to_radians();
        let x2 = sc.read::<f64>().to_radians();
        let y2 = sc.read::<f64>().to_radians();
        let theta = (x1.sin() * x2.sin() + x1.cos() * x2.cos() * (y1 - y2).abs().cos()).acos();
        writeln!(bw, "{}", (R * theta - 2.0 * R * (theta / 2.0).sin()).round() as i64).ok();
    }
}
