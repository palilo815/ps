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
    const N: usize = 100_001;
    let mut cnt = vec![0; N];
    let n = sc.read::<usize>();
    let k = sc.read::<i32>();
    let s = sc.read::<i32>();
    for _ in 0..n {
        let i = sc.read::<usize>();
        cnt[i] = sc.read::<i32>();
    }
    let (to_left, _) = (1..=s).rev().zip(cnt.iter()).fold((0, 0), |(res, mut bus), (i, &c)| {
        bus -= c;
        let x = (bus - k + 1) / k;
        (res - 2 * i * x, bus - k * x)
    });
    let (to_right, _) = cnt.iter().skip(s as usize).enumerate().rev().fold((0, 0), |(res, mut bus), (i, &c)| {
        bus -= c;
        let x = (bus - k + 1) / k;
        (res - 2 * i as i32 * x, bus - k * x)
    });
    writeln!(bw, "{}", to_left + to_right).ok();
}
