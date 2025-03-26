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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const K: usize = (b'z' - b'A' + 1) as usize;
    let n = sc.read::<usize>();
    let _ = sc.raw();
    let s = sc.raw();
    let mut key = [0; K];
    for x in s.bytes() {
        key[(x - b'A') as usize] += 1;
    }
    let s = sc.raw().as_bytes();
    let mut acc = [0; K];
    for &x in s.iter().take(n) {
        acc[(x - b'A') as usize] += 1;
    }
    let mut ans = (acc == key) as i32;
    for i in n..s.len() {
        acc[(s[i - n] - b'A') as usize] -= 1;
        acc[(s[i] - b'A') as usize] += 1;
        ans += (acc == key) as i32;
    }
    writeln!(bw, "{ans}").ok();
}
