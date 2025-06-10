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
    for t in 1.. {
        let s1 = sc.raw();
        if s1 == "END" {
            break;
        }
        let mut c1 = [0; 26];
        s1.bytes().map(|c| (c - b'a') as usize).for_each(|i| c1[i] += 1);
        let s2 = sc.raw();
        let mut c2 = [0; 26];
        s2.bytes().map(|c| (c - b'a') as usize).for_each(|i| c2[i] += 1);
        writeln!(bw, "Case {t}: {}", if c1 == c2 { "same" } else { "different" }).ok();
    }
}
