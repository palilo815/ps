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
    let mut diff = sc.read_vec::<i32>(n);
    for d in diff.iter_mut() {
        *d -= sc.read::<i32>();
    }
    let last = (diff.pop().unwrap() - diff.pop().unwrap()).abs();
    let ans = last + diff.into_iter().fold(0, |acc, x| acc + x.abs());
    writeln!(bw, "{ans}").ok();
}
