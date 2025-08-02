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
    fn next(&mut self) -> Option<&str> {
        self.it.next()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let m = sc.read::<usize>();
    let mut ans = vec![0; m];
    while let Some(s) = sc.next() {
        let mut it = s.bytes().skip(2);
        let mut num = 0;
        for _ in 0..6 {
            num = num * 10 + (it.next().unwrap_or(b'0') - b'0') as usize;
        }
        ans[num * m / 1_000_000] += 1;
    }
    for x in ans {
        write!(bw, "{x} ").ok();
    }
}
