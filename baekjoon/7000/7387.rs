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
    let mut a = [(0, 0); 6];
    a.fill_with(|| (sc.read::<u32>(), sc.read::<u32>()));
    for (x, y) in a.iter_mut() {
        if *x > *y {
            std::mem::swap(x, y);
        }
    }
    a.sort_unstable();
    let ok = a.chunks(2).all(|w| w[0] == w[1]) && a[0].0 == a[2].0 && (a[0].1, a[2].1) == a[4];
    writeln!(bw, "{}POSSIBLE", if ok { "" } else { "IM" }).ok();
}
