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
    let t = sc.read::<usize>();
    for _ in 0..t {
        let a = sc.read::<i64>();
        let op = sc.read::<char>();
        let b = sc.read::<i64>();
        let _ = sc.read::<char>();
        let c = sc.read::<i64>();
        let d = match op {
            '+' => a + b,
            '-' => a - b,
            '*' => a * b,
            '/' => a / b,
            _ => unreachable!(),
        };
        writeln!(bw, "{}", if c == d { "correct" } else { "wrong answer" }).ok();
    }
}
