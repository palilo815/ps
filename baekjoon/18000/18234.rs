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
    let t = sc.read::<usize>();
    let mut carrots = (0..n).map(|_| (sc.read::<u32>(), sc.read::<u32>())).collect::<Vec<_>>();
    carrots.sort_unstable_by(|l, r| l.1.cmp(&r.1));
    let ans = carrots
        .into_iter()
        .zip(t - n..t)
        .fold(0, |acc, ((a, p), i)| acc + a as usize + p as usize * i);
    writeln!(bw, "{ans}").ok();
}
