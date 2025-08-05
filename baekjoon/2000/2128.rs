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
    n: u32,
    mask: u32,
}

impl Gosper {
    fn new(n: u32, k: u32) -> Self {
        Self { n, mask: (1 << k) - 1 }
    }
}

impl Iterator for Gosper {
    type Item = u32;
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
    let n = sc.read::<usize>();
    let d = sc.read::<u32>();
    let k = sc.read::<u32>();
    let a = (0..n)
        .map(|_| {
            let m = sc.read::<usize>();
            (0..m).fold(0, |acc, _| acc | 1 << (sc.read::<u32>() - 1))
        })
        .collect::<Vec<_>>();
    let gosper = Gosper::new(d, k);
    let ans = gosper.map(|mask| a.iter().filter(|&&x| (x & mask) == x).count()).max().unwrap();
    writeln!(bw, "{ans}").ok();
}
