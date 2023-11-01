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
    let mut a = (0..n).map(|_| (sc.read::<usize>(), 1)).collect::<Vec<_>>();
    a.sort_unstable();
    a.dedup_by(|l, r| {
        if l.0 == r.0 {
            r.1 += 1;
            true
        } else {
            false
        }
    });
    const MAX_L: usize = 10_000_000;
    let mut sum = vec![0; MAX_L * 2 + 1];
    for (i, x) in a.iter().enumerate() {
        sum[x.0 * 2] += x.1 / 2 * x.0 * x.0;
        for y in a.iter().take(i) {
            sum[x.0 + y.0] += x.0 * y.0 * x.1.min(y.1);
        }
    }
    writeln!(out, "{}", sum.into_iter().max().unwrap()).ok();
}
