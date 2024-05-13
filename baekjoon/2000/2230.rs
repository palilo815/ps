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
    let m = sc.read::<i32>();
    let mut a = sc.read_vec::<i32>(n);
    a.sort_unstable();
    let mut ans = i32::MAX;
    let mut it = a.iter().peekable();
    for &x in a.iter() {
        while it.peek().is_some_and(|&y| y - x < m) {
            it.next();
        }
        match it.peek() {
            Some(&&y) => ans = ans.min(y - x),
            None => break,
        }
    }
    writeln!(bw, "{ans}").ok();
}
