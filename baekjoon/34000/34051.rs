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
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut s = sc.read_bytes();
    let mut t = s.clone();
    t.sort_unstable_by(|l, r| r.cmp(l));
    let mut ans = s.clone();
    let i = (0..n).position(|i| s[i] != t[i]).unwrap_or(n);
    for j in i + 1..=n {
        s[i..j].reverse();
        ans = ans.max(s.clone());
        s[i..j].reverse();
    }
    writeln!(bw, "{}", String::from_utf8(ans).unwrap()).ok();
}
