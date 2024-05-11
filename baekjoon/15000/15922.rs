use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut seg = (sc.read::<i32>(), sc.read::<i32>());
    let mut ans = 0;
    for _ in 1..n {
        let x = sc.read::<i32>();
        let y = sc.read::<i32>();
        if seg.1 < x {
            ans += seg.1 - seg.0;
            seg = (x, y);
        } else {
            seg.1 = seg.1.max(y);
        }
    }
    writeln!(bw, "{}", ans + seg.1 - seg.0).ok();
}
