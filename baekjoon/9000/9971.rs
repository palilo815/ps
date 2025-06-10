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
    fn next(&mut self) -> Option<&str> {
        self.it.next()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    while let Some(start) = sc.next() {
        if start == "ENDOFINPUT" {
            break;
        }
        while let Some(word) = sc.next() {
            if word == "END" {
                break;
            }
            let ans = word
                .bytes()
                .map(|c| match c {
                    b'a'..=b'e' | b'A'..=b'E' => c + 21,
                    b'f'..=b'z' | b'F'..=b'Z' => c - 5,
                    _ => c,
                })
                .collect::<Vec<_>>();
            write!(bw, "{} ", String::from_utf8(ans).unwrap()).ok();
        }
        writeln!(bw).ok();
    }
}
