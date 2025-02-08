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
    let n = sc.read::<i32>();
    let a = sc.read::<i32>();
    let b = sc.read::<i32>();
    let ones = n - a - b + 1;
    if ones.is_negative() {
        writeln!(bw, "-1").ok();
        return;
    }
    if a != 1 {
        for _ in 0..ones {
            write!(bw, "1 ").ok();
        }
    }
    for i in 1..a {
        write!(bw, "{i} ").ok();
    }
    write!(bw, "{} ", a.max(b)).ok();
    if a == 1 {
        for _ in 0..ones {
            write!(bw, "1 ").ok();
        }
    }
    for i in (1..b).rev() {
        write!(bw, "{i} ").ok();
    }
}
