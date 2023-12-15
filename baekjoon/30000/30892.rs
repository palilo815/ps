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

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut t = sc.read::<i64>();
    let mut a = (0..n).map(|_| sc.read::<i64>()).chain(std::iter::once(i64::MAX)).collect::<Vec<_>>();
    a.sort_unstable();
    let mut stack = Vec::with_capacity(n);
    let mut it = a.iter().peekable();
    for _ in 0..k {
        while t > **it.peek().unwrap() {
            stack.push(*it.next().unwrap());
        }
        t += stack.pop().unwrap_or_default();
    }
    writeln!(out, "{t}").ok();
}
