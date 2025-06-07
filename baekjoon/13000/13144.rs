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
    let n = sc.read::<usize>();
    let a = sc.read_vec::<usize>(n);
    let mut check = [false; 100_001];
    let mut ans = 0;
    let mut r = 0;
    for l in 0..n {
        while r != n && !check[a[r]] {
            check[a[r]] = true;
            r += 1;
        }
        ans += r - l;
        check[a[l]] = false;
    }
    writeln!(bw, "{}", ans).ok();
}
