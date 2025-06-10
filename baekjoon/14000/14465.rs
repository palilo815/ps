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
    let k = sc.read::<usize>();
    let b = sc.read::<usize>();
    let mut broken = vec![0; n];
    for _ in 0..b {
        broken[sc.read::<usize>() - 1] = 1;
    }
    let mut acc = broken.iter().take(k).sum::<i32>();
    let mut ans = acc;
    for i in k..n {
        acc += broken[i] - broken[i - k];
        ans = ans.min(acc);
    }
    writeln!(bw, "{ans}").ok();
}
