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
    const N: usize = 1_000_000;
    let mut a = vec![0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        a.fill_with(|| sc.read::<u32>());
        let (ans, _) = a.iter().rev().fold((0, 0), |(acc, mx), &x| {
            let mx = mx.max(x);
            (acc + (mx - x) as u64, mx)
        });
        writeln!(bw, "{ans}").ok();
    }
}

