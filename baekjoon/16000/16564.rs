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
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let k = sc.read::<i32>();
    let a = sc.read_vec::<i32>(n);
    let parametric = |mut lo, mut hi| {
        let f = |mid| -> bool {
            let mut k = k;
            for &x in a.iter().filter(|&&x| x < mid) {
                k -= mid - x;
                if k < 0 {
                    return false;
                }
            }
            true
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
    writeln!(out, "{}", parametric(1, 2_000_000_000)).ok();
}
