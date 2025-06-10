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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    loop {
        let abc = sc.raw();
        if abc == "0 0 0" {
            break;
        }
        let sum = abc.split_ascii_whitespace().map(|s| s.parse::<usize>().unwrap()).sum::<usize>();
        let shift = 26 - (sum % 25 + 1) as u8;
        let s = sc.raw();
        let t = s
            .bytes()
            .map(|c| {
                if c.is_ascii_lowercase() {
                    (c - b'a' + shift) % 26 + b'a'
                } else {
                    c
                }
            })
            .collect::<Vec<_>>();
        writeln!(bw, "{}", String::from_utf8(t).unwrap()).ok();
    }
}
