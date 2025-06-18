use std::io::*;

struct Scanner {
    it: std::str::Split<'static, char>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split('\n') }
    }
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let mut s = sc.read_bytes();
    let key = sc.read_bytes();
    for (s, k) in s.iter_mut().zip(key.into_iter().cycle()) {
        if s.is_ascii_lowercase() {
            *s = if *s > k { *s - 1 } else { *s + 25 } - k + b'a';
        }
    }
    writeln!(bw, "{}", String::from_utf8(s).unwrap()).ok();
}
