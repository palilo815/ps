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
    let mut a = sc.read_vec::<u32>(n);
    a.sort_unstable();
    let k = n * (n - 1) / 2;
    let parametric = |mut lo, mut hi| {
        let f = |mid| -> bool {
            let mut acc = 0;
            let mut j = n;
            for i in 0..n {
                while j != 0 && a[i] + a[j - 1] > mid {
                    j -= 1;
                }
                acc += j - if i < j { 1 } else { 0 };
                if acc >= k {
                    return true;
                }
            }
            false
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
    writeln!(out, "{}", parametric(2, 2_000_000_000)).ok();
}
