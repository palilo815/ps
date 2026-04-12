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
    let a = (0..n).map(|_| (sc.read::<u32>(), sc.read::<u32>())).collect::<Vec<_>>();
    let mut fartest = 0;
    let mut ans = (0, 0);
    for (i, (x1, y1)) in a.iter().enumerate() {
        for (j, &(x2, y2)) in a.iter().enumerate().take(i) {
            let d = x1.abs_diff(x2) + y1.abs_diff(y2);
            if d > fartest {
                fartest = d;
                ans = (j, i);
            }
        }
    }
    writeln!(bw, "{} {}", ans.0 + 1, ans.1 + 1).ok();
}
