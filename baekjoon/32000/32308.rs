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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<u64>();
    let mut a = sc.read_vec::<u64>(n as usize);
    a.sort_unstable();
    let total = a.iter().sum::<u64>() as f64;
    let mut acc = 0.0;
    let mut best = f64::MIN;
    for (i, w) in (1..n).zip(a.into_iter().rev()) {
        acc += w as f64;
        let x = i as f64 / n as f64;
        let y = acc / total;
        best = best.max(y - x);
    }
    writeln!(bw, "{:.8}", best * 100.0).ok();
}
