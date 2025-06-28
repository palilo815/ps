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
    let mut a = (0..n).map(|_| (sc.read::<f32>() * 10.0) as i32).collect::<Vec<_>>();
    a.select_nth_unstable(n - k - 1);
    a[..n - k - 1].select_nth_unstable(k);
    let c = a[k] + a[n - k - 1];
    let sum = a.into_iter().take(n - k).skip(k).sum::<i32>();
    let avg1 = 100 * sum / (n - 2 * k) as i32;
    let avg2 = 100 * (sum + c * k as i32) / n as i32;
    let avg1 = if avg1 % 10 < 5 { avg1 / 10 } else { avg1 / 10 + 1 };
    let avg2 = if avg2 % 10 < 5 { avg2 / 10 } else { avg2 / 10 + 1 };
    writeln!(bw, "{}.{}{}", avg1 / 100, avg1 / 10 % 10, avg1 % 10).ok();
    writeln!(bw, "{}.{}{}", avg2 / 100, avg2 / 10 % 10, avg2 % 10).ok();
}
