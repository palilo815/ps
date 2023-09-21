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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let t = sc.read::<i32>();
    let mut a = sc.read_vec::<i32>(n);
    a.sort_unstable();
    a.iter_mut().take_while(|x| **x <= t).for_each(|x| *x = t);
    let parametric = |mut lo, mut hi| {
        let mut end = vec![0; n];
        let mut f = |mid| -> bool {
            end[..mid].copy_from_slice(&a[..mid]);
            for i in mid..n {
                if end[i - mid] >= a[i] {
                    return false;
                }
                end[i] = a[i].max(end[i - mid] + t);
            }
            true
        };
        // first true
        while lo != hi {
            let mid = lo + (hi - lo) / 2;
            if f(mid) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        lo
    };
    writeln!(out, "{}", parametric(1, n)).ok();
}
