use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
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
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let s = sc.read::<usize>();
    let c = sc.read::<i32>();
    let pa = sc.read_vec::<i32>(s);
    let total = pa.iter().fold(0, |acc, &x| acc + x as i64);
    let parametric = |mut lo, mut hi| {
        let f = |mid: i32| -> bool {
            let mut left = c;
            for l in pa.iter() {
                left -= l / mid;
                if left <= 0 {
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
    let l = parametric(1, *pa.iter().max().unwrap());
    writeln!(bw, "{}", total - l as i64 * c as i64).ok();
}
