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
    let t = sc.read::<usize>();
    for t in 1..t + 1 {
        let d = sc.read::<usize>();
        let n = sc.read::<usize>();
        if d - 1 > (n - 1) * (n - 1) {
            writeln!(bw, "Grid #{t}: impossible\n").ok();
        } else {
            writeln!(bw, "Grid #{t}: {}\n", d * 2 * (n - 1)).ok();
        }
    }
}
