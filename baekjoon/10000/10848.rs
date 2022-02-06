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
    ans: T, // sum(righ) - sum(left)
}

#[allow(dead_code)]
impl<T> RunningMedian<T>
where
    T: std::cmp::Ord
        + std::marker::Copy
        + std::default::Default
        + std::ops::Add<Output = T>
        + std::ops::Sub<Output = T>,
{
    fn with_capacity(n: usize) -> Self {
        Self {
            left: std::collections::BinaryHeap::with_capacity((n + 1) >> 1),
            right: std::collections::BinaryHeap::with_capacity((n + 1) >> 1),
            ans: Default::default(),
        }
    }
    fn clear(&mut self) {
        self.left.clear();
        self.right.clear();
        self.ans = Default::default();
    }
    fn push(&mut self, mut x: T) {
        if self.left.len() == self.right.len() {
            if let Some(mut right_min) = self.right.peek_mut() {
                if x > right_min.0 {
                    self.ans = self.ans + x - right_min.0;
                    std::mem::swap(&mut x, &mut right_min.0);
                }
            }
            self.left.push(x);
            self.ans = self.ans - x;
        } else {
            let mut left_max = self.left.peek_mut().unwrap();
            if x < *left_max {
                self.ans = self.ans + *left_max - x;
                std::mem::swap(&mut x, &mut left_max);
            }
            self.right.push(std::cmp::Reverse(x));
            self.ans = self.ans + x;
        }
    }
    fn calc(&self) -> T {
        self.ans
    }
    fn get_median(&mut self) -> Option<&T> {
        self.left.peek()
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let k = sc.next::<u32>();
    let n = sc.next::<usize>();
    let mut ans = 0;
    let mut a = Vec::with_capacity(n);
    for _ in 0..n {
        let p = sc.next::<char>();
        let s = sc.next::<i32>();
        let q = sc.next::<char>();
        let t = sc.next::<i32>();
        if p == q {
            ans += (s - t).abs() as i64;
        } else {
            a.push((s, t));
        }
    }
    ans += a.len() as i64;
    a.sort_unstable_by_key(|x| x.0 + x.1);
    let mut running_median = RunningMedian::with_capacity(a.len());
    let mut dp = vec![0; a.len() + 1];
    for (x, (s, t)) in dp.iter_mut().skip(1).zip(a.iter()) {
        running_median.push(*s as i64);
        running_median.push(*t as i64);
        *x = running_median.calc();
    }
    if k == 1 {
        writeln!(out, "{}", *dp.last().unwrap() + ans).ok();
        return;
    }
    running_median.clear();
    for (x, (s, t)) in dp.iter_mut().rev().skip(1).zip(a.iter().rev()) {
        running_median.push(*s as i64);
        running_median.push(*t as i64);
        *x += running_median.calc();
    }
    writeln!(out, "{}", dp.into_iter().min().unwrap() + ans).ok();
}
