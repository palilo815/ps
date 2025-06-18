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
    let x = sc.raw();
    let mut step = 0;
    let mut x = if x.len() == 1 {
        x.parse::<u32>().unwrap()
    } else {
        step += 1;
        x.bytes().fold(0, |acc, c| acc + (c - b'0') as u32)
    };
    while x > 9 {
        let mut y = 0;
        while x != 0 {
            y += x % 10;
            x /= 10;
        }
        x = y;
        step += 1;
    }
    writeln!(bw, "{step}\n{}", if x % 3 == 0 { "YES" } else { "NO" }).ok();
}
