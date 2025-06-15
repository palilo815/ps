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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let s = sc.raw();
    let sum = s.bytes().fold(0, |acc, c| {
        acc + match c {
            b'a'..=b'z' => (c - b'a' + 1) as usize,
            b'A'..=b'Z' => (c - b'A' + 27) as usize,
            _ => unreachable!(),
        }
    });
    let is_prime = (2..sum).all(|x| sum % x != 0);
    writeln!(bw, "It is {}a prime word.", if is_prime { "" } else { "not " }).ok();
}
