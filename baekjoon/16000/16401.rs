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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let m = sc.read::<i32>();
    let n = sc.read::<usize>();
    let a = sc.read_vec::<i32>(n);
    let parametric = |mut lo, mut hi| {
        let f = |mid| -> bool { a.iter().fold(0_i32, |acc, &x| acc.saturating_add(x / mid)) >= m };
        // last true
        while lo != hi {
            let mid = hi - (hi - lo) / 2;
            if f(mid) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        lo
    };
    let ans = parametric(0, *a.iter().max().unwrap());
    writeln!(bw, "{ans}").ok();
}
