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
    let a = sc.read_vec::<usize>(n);
    let mut b = a.clone().into_iter().enumerate().collect::<Vec<_>>();
    b.sort_unstable_by(|l, r| l.1.cmp(&r.1));
    let mut check = vec![0; n];
    let mut len = n;
    let mut acc = 0;
    let mut ans = (0, 0);
    for (i, x) in b {
        while m < len * x {
            len -= 1;
            acc -= check[len];
        }
        if i < len {
            acc += 1;
            check[i] = 1;
        }
        ans = ans.min((-acc - if len == n { 0 } else { (a[len] <= m - len * x) as i32 }, x));
    }
    writeln!(out, "{}", ans.1).ok();
}
