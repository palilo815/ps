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
    loop {
        let a = sc.read::<String>();
        let b = sc.read::<String>();
        if a == "#" {
            break;
        }
        let n = sc.read::<usize>();
        let same = (0..n).filter(|_| sc.read::<char>() == sc.read::<char>()).count();
        let diff = n - same;
        writeln!(bw, "{a} {same} {b} {diff}").ok();
    }
}
