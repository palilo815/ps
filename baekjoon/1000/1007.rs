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

struct Gosper {
    n: usize,
    mask: usize,
}

impl Gosper {
    fn new(n: usize, k: usize) -> Self {
        Self { n, mask: (1 << k) - 1 }
    }
}

impl Iterator for Gosper {
    type Item = usize;
    fn next(&mut self) -> Option<Self::Item> {
        if self.mask >= 1 << self.n {
            return None;
        }
        let x = self.mask;
        let c = x & x.wrapping_neg();
        let r = x + c;
        let y = (((r ^ x) >> 2) / c) | r;
        self.mask = y;
        Some(x)
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 20;
    let mut points = [(0, 0); N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let points = &mut points[..n];
        points.fill_with(|| (sc.read::<i64>(), sc.read::<i64>()));
        let gosper = Gosper::new(n, n / 2);
        let ans = gosper
            .into_iter()
            .map(|mask| {
                let (x, y) = (0..n).fold((0, 0), |(x, y), i| {
                    if mask >> i & 1 == 0 {
                        (x + points[i].0, y + points[i].1)
                    } else {
                        (x - points[i].0, y - points[i].1)
                    }
                });
                x * x + y * y
            })
            .min()
            .unwrap();
        let ans = (ans as f64).sqrt();
        writeln!(bw, "{ans:.8}").ok();
    }
}
