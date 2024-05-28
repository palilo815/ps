use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let h = sc.read::<u64>();
    if !h.is_power_of_two() {
        writeln!(bw, "-1").ok();
        return;
    }
    let p = h.ilog2();
    if p < 4 || !p.is_power_of_two() {
        writeln!(bw, "-1").ok();
        return;
    }
    let p2 = p.ilog2();
    writeln!(bw, "{} {}", p2 + 1, p2 + 1).ok();
    for _ in 0..p2 {
        write!(bw, "1 ").ok();
    }
    writeln!(bw).ok();
    for _ in 1..p2 {
        write!(bw, "1 ").ok();
    }
    writeln!(bw, "2").ok();
}
