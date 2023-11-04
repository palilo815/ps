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
    let mut delta = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    delta.sort_unstable_by(|l, r| (r.0 - l.1).cmp(&(l.0 - r.1)));
    let a = delta.iter().step_by(2).fold(0, |acc, x| acc + x.0);
    let b = delta.iter().skip(1).step_by(2).fold(0, |acc, x| acc + x.1);
    writeln!(out, "{}", a - b).ok();
}
