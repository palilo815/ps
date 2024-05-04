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
    let m = sc.read::<u32>();
    let a = sc.read_vec::<u32>(n);
    let mut r = 0;
    let mut acc = 0;
    let mut ans = 0;
    for l in 0..n {
        while r != n && acc < m {
            acc += a[r];
            r += 1;
        }
        ans += (acc == m) as i32;
        acc -= a[l];
    }
    writeln!(bw, "{ans}").ok();
}
