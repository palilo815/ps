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
    const N: usize = 800;
    let mut a = [0; N];
    let mut b = [0; N];
    let t = sc.read::<usize>();
    for t in 1..=t {
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        let b = &mut b[..n];
        a.fill_with(|| sc.read::<i64>());
        b.fill_with(|| sc.read::<i64>());
        a.sort_unstable();
        b.sort_unstable();
        let ans = a.iter().zip(b.iter().rev()).map(|x| x.0 * x.1).sum::<i64>();
        writeln!(bw, "Case #{t}: {ans}").ok();
    }
}
