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
    let mut bugs = (0..n).map(|_| (sc.read::<usize>(), sc.read::<usize>())).collect::<Vec<_>>();
    bugs.sort_unstable_by(|l, r| r.1.cmp(&l.1));
    let parametric = |mut lo, mut hi| {
        let mut pq = std::collections::BinaryHeap::with_capacity(n + 1);
        let mut f = |mid| -> bool {
            let mut acc = bugs.iter().take(mid).fold(0, |acc, x| acc + x.0);
            if acc <= mid * bugs[mid - 1].1 {
                return true;
            }
            pq.clear();
            pq.extend(bugs.iter().take(mid).map(|x| x.0));
            for &(a, b) in bugs.iter().skip(mid) {
                if *pq.peek().unwrap() > a {
                    acc -= *pq.peek().unwrap() - a;
                    *pq.peek_mut().unwrap() = a;
                }
                if acc <= mid * b {
                    return true;
                }
            }
            false
        };
        // last true
        while lo != hi {
            let mid = hi - (hi - lo) / 2;
            if f(mid) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        lo
    };
    let ans = parametric(0, n);
    writeln!(out, "{ans}").ok();
}
