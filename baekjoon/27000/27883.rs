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
    let _ = sc.read::<usize>();
    let m = sc.read::<usize>();
    writeln!(bw, "{}", 2 * m + 1).ok();
    writeln!(bw, "U 1 -10000").ok();
    for i in 1..=m {
        let x = sc.read::<usize>();
        writeln!(bw, "U {} {}", x + 1, i).ok();
        writeln!(bw, "P").ok();
    }
}

