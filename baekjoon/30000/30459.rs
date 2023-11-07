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
    let m = sc.read::<usize>();
    let r = sc.read::<i32>() * 2;
    let mut a = sc.read_vec::<i32>(n);
    let mut b = sc.read_vec::<i32>(m);
    a.sort_unstable();
    b.sort_unstable();
    let mut ans = 0;
    for (i, &x1) in a.iter().enumerate() {
        let mut h = b.iter().rev().peekable();
        for &x2 in a.iter().skip(i + 1) {
            let x = x2 - x1;
            while *h.peek().unwrap_or(&&0) * x > r {
                h.next();
            }
            if let Some(&&y) = h.peek() {
                ans = ans.max(x * y);
            } else {
                break;
            }
        }
    }
    if ans == 0 {
        writeln!(out, "-1").ok();
    } else {
        writeln!(out, "{}.{}", ans / 2, ans % 2 * 5).ok();
    }
}
