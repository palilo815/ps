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
    let a = sc.read_vec(n);
    let mut dq = std::collections::VecDeque::with_capacity(n);
    for (c, x) in a.into_iter().rev().zip(1..) {
        match c {
            '1' => dq.push_front(x),
            '3' => dq.push_back(x),
            _ => {
                let y = std::mem::replace(dq.front_mut().unwrap(), x);
                dq.push_front(y);
            }
        }
    }
    for x in dq {
        write!(out, "{x} ").ok();
    }
}
