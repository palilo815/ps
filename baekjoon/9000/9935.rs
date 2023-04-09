use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let mut s = sc.read_bytes();
    let k = sc.read_bytes();
    let n = s.len();
    let m = k.len();
    let mut i = 0;
    for j in 0..n {
        s[i] = s[j];
        i += 1;
        if i >= m && s[i - m..i].eq(&k) {
            i -= m;
        }
    }
    s.truncate(i);
    let s = if i == 0 {
        String::from("FRULA")
    } else {
        String::from_utf8(s).unwrap()
    };
    writeln!(out, "{s}").ok();
}
