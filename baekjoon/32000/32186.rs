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
    let n = sc.read::<usize>();
    let k = sc.read::<u64>();
    let a = sc.read_vec::<u32>(n);
    let mut ans = 0;
    for (&x, &y) in a.iter().zip(a.iter().rev()).take(a.len() / 2) {
        let mut diff = x.abs_diff(y) as u64;
        ans += diff / k;
        diff %= k;
        ans += diff.min(k - diff + 1);
    }
    writeln!(bw, "{ans}").ok();
}
