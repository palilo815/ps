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
    const X: f64 = (100 * 60 * 60 * 24) as f64;
    let f = |h: u32, m: u32, s: u32, u: u32| -> u32 { u + s * 100 + m * 100 * 60 + h * 100 * 60 * 60 };
    let t = sc.read::<usize>();
    for tc in 1..=t {
        let a1 = f(sc.read(), sc.read(), sc.read(), sc.read());
        let a2 = f(sc.read(), sc.read(), sc.read(), sc.read());
        let r = sc.read::<f64>();
        let theta = a1.abs_diff(a2) as f64 / X;
        writeln!(bw, "{tc}. {:.3}", std::f64::consts::TAU * r * r * theta).ok();
    }
}
