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
    let n = sc.read::<i64>();
    let r = sc.read::<i64>();
    let n = n - r;
    let mut ans = 0;
    let mut i = 1_i64;
    while i * i <= n {
        if n % i == 0 {
            if i > r {
                ans += i;
            }
            if i * i != n && n / i > r {
                ans += n / i;
            }
        }
        i += 1;
    }
    writeln!(out, "{ans}").ok();
}
