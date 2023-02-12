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
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
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
    let _ = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut s = sc.read_bytes();
    let check = |c: u8| c == b'A' || c == b'E' || c == b'I' || c == b'O' || c == b'U';
    while check(*s.last().unwrap_or(&b'A')) {
        s.pop();
    }
    let mut ans = vec![];
    if let Some(c) = s.pop() {
        ans.push(c);
    }
    while *s.last().unwrap_or(&b'A') != b'A' {
        s.pop();
    }
    if let Some(c) = s.pop() {
        ans.push(c);
    }
    while *s.last().unwrap_or(&b'A') != b'A' {
        s.pop();
    }
    if let Some(c) = s.pop() {
        ans.push(c);
    }
    if ans.len() != 3 || s.len() + 3 < m {
        writeln!(out, "NO").ok();
    } else {
        ans.reverse();
        s.resize(m - 3, b'?');
        writeln!(out, "YES").ok();
        write!(out, "{}", String::from_utf8(s).unwrap()).ok();
        write!(out, "{}", String::from_utf8(ans).unwrap()).ok();
    }
}
