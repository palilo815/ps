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
        let c = sc.read::<char>();
        if c == 'C' {
            for _ in 0..n {
                write!(bw, "{} ", sc.read::<char>() as u8 - b'A' + 1).ok();
            }
            writeln!(bw).ok();
        } else {
            for _ in 0..n {
                write!(bw, "{} ", (sc.read::<u8>() - 1 + b'A') as char).ok();
            }
            writeln!(bw).ok();
        }
    }
}
