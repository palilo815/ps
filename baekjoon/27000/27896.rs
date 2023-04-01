use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<i64>();
    let mut pq = std::collections::BinaryHeap::with_capacity(n);
    let mut acc = 0;
    for _ in 0..n {
        let x = sc.read::<i64>();
        pq.push(x);
        acc += x;
        if acc >= m {
            acc -= pq.pop().unwrap() * 2;
        }
    }
    writeln!(out, "{}", n - pq.len()).ok();
}
