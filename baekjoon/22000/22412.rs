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
    const ABC: [u8; 3] = [0, 1, 2];
    let mut s = sc.read_bytes();
    s.iter_mut().for_each(|c| *c -= b'A');
    let mut t = Vec::with_capacity(s.len());
    let mut check = [0; 4];
    while s.len() > 3 {
        let mut i = 0;
        t.clear();
        while i != s.len() {
            if i + 3 <= s.len() && s[i..i + 3].eq(&ABC) {
                t.push(3);
                i += 3;
            } else {
                t.push(s[i]);
                i += 1;
            }
        }
        check.fill(0);
        for &c in t.iter() {
            check[c as usize] = 1;
        }
        if check[3] == 0 || check[0] + check[1] + check[2] != 2 {
            writeln!(bw, "No").ok();
            return;
        }
        let x = check.iter().position(|&c| c != 1).unwrap() as u8;
        for c in t.iter_mut() {
            if *c == 3 {
                *c = x;
            }
        }
        std::mem::swap(&mut s, &mut t);
    }
    let ans = if s.eq(&ABC) { "Yes" } else { "No" };
    writeln!(bw, "{ans}").ok();
}
