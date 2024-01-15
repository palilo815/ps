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
    let a = sc.read_vec::<i32>(n);
    let parametric = |mut lo, mut hi| {
        let f = |mid| -> bool {
            let mut min = 1_000_000_000;
            let mut prv = min;
            let mut cur = 0;
            for &x in a.iter() {
                min = min.min(prv);
                prv = cur;
                cur += if x < mid { -1 } else { 1 };
                if cur - min > 0 {
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
    writeln!(out, "{}", parametric(1, 1_000_000_000)).ok();
}
