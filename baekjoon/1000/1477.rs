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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<u32>();
    let l = sc.read::<u32>();
    let mut a = vec![0; n + 1];
    for x in a.iter_mut().take(n) {
        *x = sc.read::<u32>();
    }
    a[n] = l;
    a.sort_unstable();
    let parametric = |mut lo, mut hi| {
        let f = |mid| -> bool {
            let mut last = 0;
            let mut need = 0;
            for &x in a.iter() {
                while last + mid < x {
                    last += mid;
                    need += 1;
                }
                last = x
            }
            need <= m
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
    writeln!(bw, "{}", parametric(1, l)).ok();
}
