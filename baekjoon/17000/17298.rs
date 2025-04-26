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
    let mut h = sc.read_vec::<i32>(n);
    let mut stack = Vec::with_capacity(n);
    for x in h.iter_mut().rev() {
        while stack.last().is_some_and(|y| *y <= *x) {
            stack.pop();
        }
        stack.push(std::mem::replace(x, *stack.last().unwrap_or(&-1)));
    }
    for x in h {
        write!(bw, "{x} ").ok();
    }
}
