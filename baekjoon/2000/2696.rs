use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

struct RunningMedian<T> {
    left: std::collections::BinaryHeap<T>,
    right: std::collections::BinaryHeap<std::cmp::Reverse<T>>,
}

#[allow(dead_code)]
impl<T> RunningMedian<T>
where
    T: std::cmp::Ord + std::marker::Copy,
{
    fn new() -> Self {
        Self {
            left: Default::default(),
            right: Default::default(),
        }
    }
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
            if let Some(mut right_min) = self.right.peek_mut() {
                if x > right_min.0 {
                    std::mem::swap(&mut x, &mut right_min.0);
                }
            }
            self.left.push(x);
        } else {
            let mut left_max = self.left.peek_mut().unwrap();
            if x < *left_max {
                std::mem::swap(&mut x, &mut left_max);
            }
            self.right.push(std::cmp::Reverse(x));
        }
    }
    fn get_median(&mut self) -> Option<&T> {
        self.left.peek()
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let t = sc.next::<usize>();
    let mut running_median = RunningMedian::with_capacity(10000);
    for _ in 0..t {
        running_median.clear();
        let n = sc.next::<usize>();
        writeln!(out, "{}", (n + 1) >> 1).ok();
        for i in 0..n {
            running_median.push(sc.next::<i32>());
            if i & 1 == 0 {
                if i % 20 == 0 && i != 0 {
                    writeln!(out).ok();
                }
                write!(out, "{} ", running_median.get_median().unwrap()).ok();
            }
        }
        writeln!(out).ok();
    }
}
