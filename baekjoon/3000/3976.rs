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
    const N: usize = 99_999;
    let mut p1 = vec![0; N];
    let mut d1 = vec![0; N];
    let mut p2 = vec![0; N];
    let mut d2 = vec![0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let dp1 = sc.read::<u32>();
        let dp2 = sc.read::<u32>();
        let s1 = sc.read::<u32>();
        let s2 = sc.read::<u32>();
        let p1 = &mut p1[..n - 1];
        let d1 = &mut d1[..n - 1];
        let p2 = &mut p2[..n - 1];
        let d2 = &mut d2[..n - 1];
        p1.fill_with(|| sc.read());
        d1.fill_with(|| sc.read());
        p2.fill_with(|| sc.read());
        d2.fill_with(|| sc.read());
        let (dp1, dp2) = (0..n - 1).fold((dp1, dp2), |(dp1, dp2), i| {
            ((dp1 + d1[i]).min(dp2 + p2[i]), (dp2 + d2[i]).min(dp1 + p1[i]))
        });
        writeln!(bw, "{}", (dp1 + s1).min(dp2 + s2)).ok();
    }
}
