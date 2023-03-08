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
    let mut a = (0..n)
        .map(|_| (sc.read::<i32>(), sc.read::<i32>()))
        .collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    let best = a
        .iter()
        .fold((0, 0), |best, (price, _)| {
            let earn = a
                .iter()
                .filter(|(want, charge)| price <= want && price > charge)
                .fold(0, |acc, x| acc + price - x.1);
            if earn > best.1 {
                (*price, earn)
            } else {
                best
            }
        })
        .0;
    writeln!(out, "{best}").ok();
}
