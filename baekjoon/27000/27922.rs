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
    let k = sc.read::<usize>();
    let mut a = (0..n)
        .map(|_| (sc.read::<u32>(), sc.read::<u32>(), sc.read::<u32>()))
        .collect::<Vec<_>>();
    a.select_nth_unstable_by(k - 1, |l, r| (r.0 + r.1).cmp(&(l.0 + l.1)));
    let ab = a.iter().take(k).fold(0, |acc, x| acc + x.0 + x.1);
    a.select_nth_unstable_by(k - 1, |l, r| (r.1 + r.2).cmp(&(l.1 + l.2)));
    let bc = a.iter().take(k).fold(0, |acc, x| acc + x.1 + x.2);
    a.select_nth_unstable_by(k - 1, |l, r| (r.2 + r.0).cmp(&(l.2 + l.0)));
    let ca = a.iter().take(k).fold(0, |acc, x| acc + x.2 + x.0);
    writeln!(out, "{}", ab.max(bc.max(ca))).ok();
}
