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
    const WIN: &str = "NARUTO";
    const DRAW: &str = "DRAW";
    const LOSE: &str = "SASUKE";
    let t = sc.read::<usize>();
    for _ in 0..t {
        let x = sc.read::<u64>();
        let y = sc.read::<u64>();
        let x_atk = sc.read::<u64>();
        let x_heal = sc.read::<u64>();
        let y_atk = sc.read::<u64>();
        let y_heal = sc.read::<u64>();
        if x_atk >= y {
            writeln!(bw, "{WIN}").ok();
            continue;
        }
        let x = (x + y_atk - 1) / y_atk;
        let y = (y + x_atk - 1) / x_atk;
        if x_atk > y_heal && (x_heal > y_atk || x >= y) {
            writeln!(bw, "{WIN}").ok();
            continue;
        }
        if y_atk > x_heal && (y_heal > x_atk || x < y) {
            writeln!(bw, "{LOSE}").ok();
            continue;
        }
        writeln!(bw, "{DRAW}").ok();
    }
}
