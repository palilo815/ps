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
    loop {
        let (n, t1, t2, t3) = (sc.read::<i32>(), sc.read::<i32>(), sc.read::<i32>(), sc.read::<i32>());
        if n == 0 {
            break;
        }
        writeln!(bw, "{}", 4 * n - 1 + (t2 + n - t1) % n + (t2 + n - t3) % n).ok();
    }
}
