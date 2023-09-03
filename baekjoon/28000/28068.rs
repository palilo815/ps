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
    let (mut first, mut second): (Vec<_>, Vec<_>) =
        (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).partition(|x| x.0 < x.1);
    first.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    second.sort_unstable_by(|l, r| r.1.cmp(&l.1));
    let mut acc = 0;
    for (a, b) in first.into_iter().chain(second.into_iter()) {
        if acc < a as i64 {
            writeln!(out, "0").ok();
            return;
        }
        acc += (b - a) as i64;
    }
    writeln!(out, "1").ok();
}
