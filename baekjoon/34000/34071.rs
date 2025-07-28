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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let first = sc.read::<u32>();
    let mut ez = true;
    let mut hard = true;
    for _ in 1..n {
        let x = sc.read::<u32>();
        ez &= first < x;
        hard &= first > x;
    }
    let ans = match (ez, hard) {
        (true, true) => unreachable!(),
        (true, false) => "ez",
        (false, true) => "hard",
        (false, false) => "?",
    };
    writeln!(bw, "{ans}").ok();
}
