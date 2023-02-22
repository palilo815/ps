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
    let mut acc = 0;
    let mut mn = 0;
    let mut mx = 0;
    let mut best = 0;
    for _ in 0..n {
        acc += if sc.read::<char>() == '1' { 1 } else { -1 };
        best = best.max((acc - mn).max(mx - acc));
        mn = mn.min(acc);
        mx = mx.max(acc);
    }
    writeln!(out, "{best}").ok();
}
