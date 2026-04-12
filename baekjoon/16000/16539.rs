use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = Vec::new();
        stdin().lock().read_to_end(&mut buf).ok();
        let s = unsafe { std::str::from_utf8_unchecked(Box::leak(buf.into_boxed_slice())) };
        Self { it: s.split_ascii_whitespace() }
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
    let mut a = sc.read_vec::<u32>(n);
    let mut stk = Vec::with_capacity(n);
    for x in a.iter_mut().rev() {
        let xx = *x;
        while stk.last().is_some_and(|y| *y <= xx) {
            stk.pop();
        }
        *x = stk.len() as u32;
        stk.push(xx);
    }
    for x in a {
        write!(bw, "{x} ").ok();
    }
}
