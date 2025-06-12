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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let a = sc.read_bytes();
    let b = sc.read_bytes();
    let c = a.iter().zip(b.iter()).map(|x| x.0 & x.1).collect();
    writeln!(bw, "{}", String::from_utf8(c).unwrap()).ok();
    let c = a.iter().zip(b.iter()).map(|x| x.0 | x.1).collect();
    writeln!(bw, "{}", String::from_utf8(c).unwrap()).ok();
    let c = a.iter().zip(b.iter()).map(|x| x.0 ^ x.1 ^ b'0').collect();
    writeln!(bw, "{}", String::from_utf8(c).unwrap()).ok();
    let c = a.into_iter().map(|x| x ^ 1).collect();
    writeln!(bw, "{}", String::from_utf8(c).unwrap()).ok();
    let c = b.into_iter().map(|x| x ^ 1).collect();
    writeln!(bw, "{}", String::from_utf8(c).unwrap()).ok();
}
