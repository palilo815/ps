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
    let n = sc.read::<u32>();
    let mut dq = (1..=n).collect::<std::collections::VecDeque<_>>();
    while dq.len() != 1 {
        dq.pop_front();
        let x = dq.pop_front().unwrap();
        dq.push_back(x);
    }
    writeln!(bw, "{}", dq.front().unwrap()).ok();
}
