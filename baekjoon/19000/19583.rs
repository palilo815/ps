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
    fn read_array<const N: usize>(&mut self) -> [u8; N] {
        let s = self.it.next().unwrap();
        let mut a = [0; N];
        a[..s.len()].copy_from_slice(s.as_bytes());
        a
    }
    fn raw(&mut self) -> Option<&str> {
        self.it.next()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let parse_time = |s: &str| s.bytes().fold(0, |acc, x| acc << 6 | x as u32);
    let s = parse_time(sc.raw().unwrap());
    let e = parse_time(sc.raw().unwrap());
    let q = parse_time(sc.raw().unwrap());
    let mut check = std::collections::HashMap::new();
    while let Some(t) = sc.raw() {
        let t = parse_time(t);
        let name = sc.read_array::<20>();
        if t <= s {
            *check.entry(name).or_insert(0) |= 1;
        } else if e <= t && t <= q {
            *check.entry(name).or_insert(0) |= 2;
        }
    }
    writeln!(bw, "{}", check.into_values().filter(|&x| x == 3).count()).ok();
}
