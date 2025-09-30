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
    let q = sc.read::<usize>();
    for _ in 0..q {
        let ta = sc.read::<u32>();
        let tb = sc.read::<u32>();
        let va = sc.read::<u32>();
        let vb = sc.read::<u32>();
        let ans = (0..=va).map(|x| (x * ta).max((va - x) * ta + vb * tb)).min().unwrap();
        writeln!(bw, "{ans}").ok();
    }
}
