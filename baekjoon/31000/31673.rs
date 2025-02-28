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
    let m = sc.read::<usize>();
    let mut v = sc.read_vec::<i32>(n);
    v.sort_unstable();
    let total = v.iter().fold(0, |acc, &x| acc + x as usize);
    let mut acc = 0;
    for (i, x) in v.into_iter().rev().enumerate() {
        acc += x as usize;
        if acc * 2 >= total {
            writeln!(bw, "{}", m / (i + 2)).ok();
            return;
        }
    }
}
