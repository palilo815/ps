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
    let m = sc.read::<i32>();
    let k = sc.read::<i32>();
    let mut a = sc.read_vec::<i32>(n);
    a.sort_unstable();
    let mut need = m * k;
    for (i, x) in a.into_iter().rev().enumerate() {
        need -= x;
        if need <= 0 {
            writeln!(bw, "{}", i + 1).ok();
            return;
        }
    }
    writeln!(bw, "STRESS").ok();
}
