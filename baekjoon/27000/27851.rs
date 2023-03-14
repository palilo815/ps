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
    let ans = (0..n).fold((0, !0x3f3f3f3f3f3f3f3fi64), |(acc, prv), _| {
        let x = sc.read::<i64>();
        if k < x - prv {
            (acc + k + 1, x)
        } else {
            (acc + x - prv, x)
        }
    });
    writeln!(out, "{}", ans.0).ok();
}
