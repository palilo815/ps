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
    let n = sc.read::<usize>();
    let mut k = sc.read::<usize>();
    let s = sc.raw();
    let mut ans = Vec::with_capacity(n);
    for c in s.bytes() {
        while k != 0 && ans.last().is_some_and(|&x| x < c) {
            k -= 1;
            ans.pop();
        }
        ans.push(c);
    }
    ans.truncate(ans.len() - k);
    writeln!(bw, "{}", String::from_utf8(ans).unwrap()).ok();
}
