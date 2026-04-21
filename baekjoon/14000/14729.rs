use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = Vec::new();
        stdin().lock().read_to_end(&mut buf).ok();
        let s = unsafe { std::str::from_utf8_unchecked(Box::leak(buf.into_boxed_slice())) };
        Self { it: s.split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut a = (0..n).map(|_| (sc.read::<f64>() * 1000.0) as u32).collect::<Vec<_>>();
    a.select_nth_unstable(7);
    a[..7].sort_unstable();
    for x in a.into_iter().take(7) {
        writeln!(bw, "{}.{:03}", x / 1000, x % 1000).ok();
    }
}
