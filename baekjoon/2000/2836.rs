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
    let m = sc.read::<u32>();
    let mut a = (0..n)
        .filter_map(|_| {
            let s = sc.read::<u32>();
            let t = sc.read::<u32>();
            if s > t {
                Some((s, t))
            } else {
                None
            }
        })
        .collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| r.0.cmp(&l.0));
    let res = a.into_iter().fold((0, (m, m)), |(acc, cur), (s, t)| {
        if s < cur.1 {
            (acc + cur.0 - cur.1, (s, t))
        } else {
            (acc, (cur.0, t.min(cur.1)))
        }
    });
    writeln!(out, "{}", m + 2 * (res.0 + res.1 .0 - res.1 .1)).ok();
}
