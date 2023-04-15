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
    let mut dx = (i32::MAX, i32::MIN);
    let mut dy = (i32::MAX, i32::MIN);
    for _ in 0..n {
        let x = sc.read::<i32>();
        let y = sc.read::<i32>();
        dx.0 = dx.0.min(x);
        dx.1 = dx.1.max(x);
        dy.0 = dy.0.min(y);
        dy.1 = dy.1.max(y);
    }
    writeln!(out, "{}", (dx.1 - dx.0) * (dy.1 - dy.0)).ok();
}
