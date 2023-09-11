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
    let l = sc.read::<u32>();
    let mut ans = 0;
    let mut a = (0..n)
        .map(|_| (sc.read::<u32>(), sc.read::<u32>()))
        .filter(|(_, t)| {
            if *t > 5 {
                true
            } else {
                ans += *t as u64;
                false
            }
        })
        .collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| r.0.cmp(&l.0));
    let mut mad = 0;
    for (k, t) in a.into_iter() {
        if mad + k * t > l {
            ans += (mad + k * t - l) as u64;
            mad = l - k * t;
        }
        ans += t as u64;
        mad += k * (t - 5);
    }
    writeln!(out, "{ans}").ok();
}
