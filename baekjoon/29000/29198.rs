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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let _ = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut s = (0..n)
        .map(|_| {
            let mut count = [0; 26];
            let s = sc.raw();
            for c in s.bytes() {
                count[(c - b'A') as usize] += 1;
            }
            count
        })
        .collect::<Vec<_>>();
    s.select_nth_unstable_by(k - 1, |l, r| r.cmp(&l));
    let sum = s.into_iter().take(k).fold([0; 26], |mut acc, x| {
        acc.iter_mut().zip(x.into_iter()).for_each(|(s, x)| *s += x);
        acc
    });
    for (c, x) in ('A'..).zip(sum.into_iter()) {
        for _ in 0..x {
            write!(out, "{c}").ok();
        }
    }
}
