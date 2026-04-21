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
}

struct RunningMedian<T> {
    left: std::collections::BinaryHeap<T>,
    right: std::collections::BinaryHeap<std::cmp::Reverse<T>>,
}

impl<T: Clone + Copy + std::cmp::Ord> RunningMedian<T> {
    fn with_capacity(n: usize) -> Self {
        Self {
            left: std::collections::BinaryHeap::with_capacity((n + 1) >> 1),
            right: std::collections::BinaryHeap::with_capacity((n + 1) >> 1),
        }
    }
    fn clear(&mut self) {
        self.left.clear();
        self.right.clear();
    }
    fn push(&mut self, mut x: T) {
        if self.left.len() == self.right.len() {
            if let Some(mut r) = self.right.peek_mut()
                && x > r.0
            {
                std::mem::swap(&mut x, &mut r.0);
            }
            self.left.push(x);
        } else {
            if let Some(mut l) = self.left.peek_mut()
                && x < *l
            {
                std::mem::swap(&mut x, &mut l);
            }
            self.right.push(std::cmp::Reverse(x));
        }
    }
    fn get_median(&mut self) -> Option<&T> {
        self.left.peek()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let t = sc.read::<usize>();
    let mut rm = RunningMedian::with_capacity(10000);
    for _ in 0..t {
        rm.clear();
        let n = sc.read::<usize>();
        writeln!(bw, "{}", (n + 1) >> 1).ok();
        for i in 0..n {
            rm.push(sc.read::<i32>());
            if i & 1 == 0 {
                if i % 20 == 0 && i != 0 {
                    writeln!(bw).ok();
                }
                write!(bw, "{} ", rm.get_median().unwrap()).ok();
            }
        }
        writeln!(bw).ok();
    }
}
