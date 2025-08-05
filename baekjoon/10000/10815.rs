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
    let set = (0..n).map(|_| sc.read::<i32>()).collect::<std::collections::HashSet<_>>();
    let m = sc.read::<usize>();
    for _ in 0..m {
        let ans = set.contains(&sc.read::<i32>());
        write!(bw, "{} ", ans as i32).ok();
    }
}
