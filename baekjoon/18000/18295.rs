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
    const N: usize = 1_000_000;
    let mut check = vec![false; N];
    let n = sc.read::<usize>();
    for _ in 0..n {
        let s = sc.raw();
        if s.as_bytes()[0] == b'-' || s.len() > 6 {
            continue;
        }
        check[s.parse::<usize>().unwrap()] = true;
    }
    let ans = check.into_iter().position(|x| !x).unwrap_or(N);
    writeln!(bw, "{ans}").ok();
}
