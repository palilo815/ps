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
    let mut check = [false; 30];
    for _ in 2..30 {
        check[sc.read::<usize>() - 1] = true;
    }
    for (check, i) in check.into_iter().zip(1..) {
        if !check {
            writeln!(bw, "{i}").ok();
        }
    }
}
