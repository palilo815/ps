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
    let mut ans = 0;
    let mut parity = false;
    let mut min_odd = u32::MAX;
    for _ in 0..n {
        let x = sc.read::<u32>();
        ans += x;
        if x & 1 == 1 {
            parity ^= true;
            min_odd = min_odd.min(x);
        }
    }
    if parity {
        ans -= min_odd;
    }
    writeln!(out, "{ans}").ok();
}
