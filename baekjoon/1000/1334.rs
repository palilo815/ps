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
    let s = sc.read_bytes();
    if s.iter().all(|&x| x == b'9') {
        writeln!(bw, "1{}1", "0".repeat(s.len() - 1)).ok();
        return;
    }
    let mut t = s.clone();
    let half = s.len() / 2;
    t.copy_within(..half, s.len() - half);
    t[s.len() - half..].reverse();
    if t > s {
        writeln!(bw, "{}", String::from_utf8(t).unwrap()).ok();
        return;
    }
    let (mut i, mut j) = if s.len() % 2 == 0 {
        t[half - 1] += 1;
        t[half] += 1;
        (half - 1, half)
    } else {
        t[half] += 1;
        (half, half)
    };
    while t[i] > b'9' {
        t[i] = b'0';
        t[j] = b'0';
        i -= 1;
        j += 1;
        t[i] += 1;
        t[j] += 1;
    }
    writeln!(bw, "{}", String::from_utf8(t).unwrap()).ok();
}
