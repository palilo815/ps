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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let a = sc.read_vec::<i32>(n);
    let b = sc.read_vec::<i32>(n);
    let mut ans = a.iter().chain(b.iter()).sum::<i32>() * 3;
    for i in 0..n {
        if i + 1 != n {
            ans -= 2 * (a[i] & a[i + 1]);
            ans -= 2 * (b[i] & b[i + 1]);
        }
        if i & 1 == 0 {
            ans -= 2 * (a[i] & b[i]);
        }
    }
    writeln!(bw, "{ans}").ok();
}
