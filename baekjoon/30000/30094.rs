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
    let n = sc.read::<usize>();
    let mut a = (0..n).map(|i| (sc.read::<i64>(), sc.read::<i64>(), i)).collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| (l.1 - l.0).cmp(&(r.1 - r.0)));
    const MOD: i64 = 998_244_353;
    let num = a
        .iter()
        .fold((1, 0, i64::MAX), |(acc, dup, prv), &(l, r, _)| {
            let dup = if prv == l - r { dup + 1 } else { 1 };
            (acc * dup % MOD, dup, l - r)
        })
        .0;
    let n = n as i64;
    let mn = a.iter().fold((0, 0), |(acc, l), &(x, y, _)| (acc + l * x + (n - 1 - l) * y, l + 1));
    let mx = a.iter().rev().fold((0, 0), |(acc, l), &(x, y, _)| (acc + l * x + (n - 1 - l) * y, l + 1));
    writeln!(out, "{} {}", mn.0, num).ok();
    for x in a.iter() {
        write!(out, "{} ", x.2 + 1).ok();
    }
    writeln!(out).ok();
    writeln!(out, "{} {}", mx.0, num).ok();
    for x in a.iter().rev() {
        write!(out, "{} ", x.2 + 1).ok();
    }
}
