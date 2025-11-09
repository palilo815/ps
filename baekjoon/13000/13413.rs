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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let t = sc.read::<usize>();
    for _ in 0..t {
        let _ = sc.read::<usize>();
        let s = sc.read_bytes();
        let t = sc.read_bytes();
        let (b, w) = s.into_iter().zip(t.into_iter()).fold((0, 0), |acc, (x, y)| {
            if x == y {
                acc
            } else if x == b'B' {
                (acc.0 + 1, acc.1)
            } else {
                (acc.0, acc.1 + 1)
            }
        });
        writeln!(bw, "{}", b + w - b.min(w)).ok();
    }
}
