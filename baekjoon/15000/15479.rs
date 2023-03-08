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
    let k = sc.read::<usize>();
    let l = sc.read::<usize>();
    let a = sc.read_vec::<u32>(n);
    let parametric = |mut lo, mut hi| {
        let mut indices = Vec::with_capacity(n + 2);
        let mut f = |mid| -> bool {
            indices.clear();
            indices.push(usize::MAX);
            indices.extend((0..n).filter(|&i| a[i] < mid));
            indices.push(n);
            let s = indices
                .windows(k + 1)
                .fold(0, |acc, w| acc + (w[1] - w[0]) * (n - w[k]));
            s < l
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
    writeln!(out, "{}", parametric(1, n as u32)).ok();
}
