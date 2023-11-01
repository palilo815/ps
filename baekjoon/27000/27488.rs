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
    let t = sc.read::<usize>();
    for _ in 0..t {
        let mut n = sc.read::<usize>();
        let mut ans = [0; 2];
        let mut i = 0;
        let mut p = 1;
        while n != 0 {
            let digit = n % 10;
            ans[0] += digit / 2 * p;
            ans[1] += digit / 2 * p;
            if digit & 1 == 1 {
                ans[i] += p;
                i ^= 1;
            }
            n /= 10;
            p *= 10;
        }
        writeln!(out, "{} {}", ans[0], ans[1]).ok();
    }
}
