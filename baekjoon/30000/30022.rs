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
    let a = sc.read::<usize>();
    let _ = sc.read::<usize>();
    let mut price = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    price.select_nth_unstable_by(a - 1, |l, r| (l.0 - l.1).cmp(&(r.0 - r.1)));
    let r1 = price.iter().take(a).fold(0, |acc, x| acc + x.0 as i64);
    let r2 = price.iter().skip(a).fold(0, |acc, x| acc + x.1 as i64);
    writeln!(out, "{}", r1 + r2).ok();
}
