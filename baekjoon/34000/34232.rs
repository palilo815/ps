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
    let n = sc.read::<usize>();
    let mut pos = vec![(0, 0); n * n];
    for i in 0..n {
        for j in 0..n {
            pos[sc.read::<usize>() - 1] = (i, j);
        }
    }
    let mut x0 = usize::MAX;
    let mut x1 = 0;
    let mut y0 = usize::MAX;
    let mut y1 = 0;
    let mut ans = 0;
    for (i, (x, y)) in (1..).zip(pos) {
        x0 = x.min(x0);
        x1 = x.max(x1);
        y0 = y.min(y0);
        y1 = y.max(y1);
        if i * i == (x1 - x0 + 1).pow(2) * (y1 - y0 + 1).pow(2) {
            ans += 1;
        }
    }
    writeln!(bw, "{ans}").ok();
}
