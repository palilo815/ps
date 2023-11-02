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
    let q = sc.read::<usize>();
    for _ in 0..q {
        let mut u = sc.read::<u64>();
        let mut v = sc.read::<u64>();
        let mut ans = 0;
        while u != v {
            if u > v {
                u >>= 1;
            } else {
                v >>= 1;
            }
            ans += 1;
        }
        writeln!(out, "{ans}").ok();
    }
}
