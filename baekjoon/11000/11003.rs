use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

struct MonotoneQueue<T> {
    q: std::collections::VecDeque<(T, i32)>,
    added: i32,
    removed: i32,
}

impl<T: Copy + PartialOrd> MonotoneQueue<T> {
    fn with_capacity(capacity: usize) -> Self {
        Self {
            q: std::collections::VecDeque::with_capacity(capacity),
            added: 0,
            removed: 0,
        }
    }
    fn front(&self) -> T {
        self.q.front().unwrap().0 // unsafe
    }
    fn push(&mut self, value: T) {
        while !self.q.is_empty() && self.q.back().unwrap().0 > value {
            self.q.pop_back();
        }
        self.q.push_back((value, self.added));
        self.added += 1;
    }
    fn pop(&mut self) {
        if !self.q.is_empty() && self.q.front().unwrap().1 == self.removed {
            self.q.pop_front();
        }
        self.removed += 1;
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let l = sc.read::<usize>();
    let mut q = MonotoneQueue::with_capacity(l);
    for i in 0..n {
        if i >= l {
            q.pop();
        }
        q.push(sc.read::<i32>());
        write!(out, "{} ", q.front()).ok();
    }
}
