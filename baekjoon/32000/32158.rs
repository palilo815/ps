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
    let n = sc.read::<usize>();
    let mut s = sc.read_bytes();
    let p = (0..n).filter(|&i| s[i] == b'P').collect::<Vec<_>>();
    let c = (0..n).filter(|&i| s[i] == b'C').collect::<Vec<_>>();
    for (p, c) in p.into_iter().zip(c.into_iter()) {
        s.swap(p, c);
    }
    writeln!(bw, "{}", String::from_utf8(s).unwrap()).ok();
}
