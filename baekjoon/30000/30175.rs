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
    const N: usize = 100_000;
    let mut a = vec![0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        a.fill_with(|| sc.read::<i32>());
        a.sort_unstable();
        if n & 1 == 1 {
            write!(bw, "{} ", a[n / 2]).ok();
            for (x, y) in a[..n / 2].iter().rev().zip(a[n / 2 + 1..].iter()) {
                write!(bw, "{x} {y} ").ok();
            }
        } else {
            for (x, y) in a[..n / 2].iter().rev().zip(a[n / 2..].iter()) {
                write!(bw, "{x} {y} ").ok();
            }
        }
        writeln!(bw).ok();
    }
}
