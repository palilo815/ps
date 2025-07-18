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
    let m = sc.read::<usize>();
    let mut a = (0..n).collect::<Vec<_>>();
    for _ in 0..m {
        let l = sc.read::<usize>() - 1;
        let r = sc.read::<usize>();
        a[l..r].reverse();
    }
    for x in a {
        write!(bw, "{} ", x + 1).ok();
    }
}
