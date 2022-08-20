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
    fn raw(&mut self) -> Option<&str> {
        self.it.next()
    }
}

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let parse_time = |s: &str| s.bytes().fold(0, |acc, x| acc << 6 | x as u32);
    let s = parse_time(sc.raw().unwrap());
    let e = parse_time(sc.raw().unwrap());
    let q = parse_time(sc.raw().unwrap());
    let mut check = std::collections::HashMap::new();
    while let Some(t) = sc.raw() {
        let t = parse_time(t);
        let name = sc.raw().unwrap().to_string();
        if t <= s {
            *check.entry(name).or_insert(0) |= 1;
        } else if e <= t && t <= q {
            *check.entry(name).or_insert(0) |= 2;
        }
    }
    writeln!(out, "{}", check.into_values().filter(|&x| x == 3).count()).ok();
}
