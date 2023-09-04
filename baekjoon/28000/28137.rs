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
    let k = sc.read::<i64>();
    let mut map = std::collections::HashMap::new();
    let mut ans = 0;
    for _ in 0..n {
        let x = sc.read::<i64>();
        let y = sc.read::<i64>();
        let y_intercept = y - k * x;
        let e = map.entry(y_intercept).or_insert(0);
        ans += *e as i64;
        *e += 1;
    }
    ans *= 2;
    writeln!(out, "{ans}").ok();
}
