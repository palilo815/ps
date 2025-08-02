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
    let x = sc.read::<usize>();
    let chance_5000 = (x / 1000 - n) / 4;
    let mut ans = 0;
    let mut taste = (0..n)
        .map(|_| {
            let a = sc.read::<i32>();
            let b = sc.read::<i32>();
            ans += b;
            0.max(a - b)
        })
        .collect::<Vec<_>>();
    if chance_5000 < n {
        taste.select_nth_unstable_by(chance_5000, |l, r| r.cmp(l));
    }
    ans += taste.into_iter().take(chance_5000).sum::<i32>();
    writeln!(bw, "{ans}").ok();
}
