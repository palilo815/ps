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
    let n = sc.read::<usize>();
    let mut a = (0..n)
        .map(|_| {
            sc.raw(); // ignore
            (sc.read::<u32>(), sc.read::<u32>())
        })
        .collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| r.1.cmp(&l.1).then(l.0.cmp(&r.0)));
    a.dedup();
    let mut dp = Vec::with_capacity(n);
    dp.push(u32::MAX);
    for (x, _) in a {
        if x >= *dp.last().unwrap() {
            dp.push(x);
        } else {
            let i = dp.partition_point(|&elem| elem <= x);
            dp[i] = x;
        }
    }
    writeln!(bw, "{}", dp.len()).ok();
}
