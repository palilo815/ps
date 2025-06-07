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
    let h = sc.read_vec::<u32>(n);
    let mut stack = Vec::with_capacity(n);
    for i in 0..n {
        while stack.last().is_some_and(|&j| h[j] < h[i]) {
            stack.pop();
        }
        write!(bw, "{} ", stack.last().unwrap_or(&usize::MAX) + 1).ok();
        stack.push(i);
    }
}
