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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let a = sc.read_vec::<u32>(n);
    let mut dq = std::collections::VecDeque::new();
    for x in a.iter().take(k) {
        while dq.back().unwrap_or(&0) > x {
            dq.pop_back();
        }
        dq.push_back(*x);
    }
    let mut ans = *dq.front().unwrap();
    for (x, y) in a.iter().zip(a.iter().skip(k)) {
        if dq.front().unwrap() == x {
            dq.pop_front();
        }
        while dq.back().unwrap_or(&0) > y {
            dq.pop_back();
        }
        dq.push_back(*y);
        ans = ans.max(*dq.front().unwrap());
    }
    writeln!(out, "{ans}").ok();
}
