use std::io::Write;

pub struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn next<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn next_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.next()).collect()
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let m = sc.next::<usize>();
    let n = sc.next::<usize>();
    let mut a = sc.next_vec::<u32>(n);
    a.sort_unstable();
    let parametric = |mut lo, mut hi| {
        let f = |mid| -> bool {
            let mut prv = a[0];
            let mut chance = m - 1;
            for &x in a.iter() {
                if x - prv > mid {
                    if chance == 0 {
                        return false;
                    }
                    chance -= 1;
                    prv = x;
                }
            }
            true
        };
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
    let ans = parametric(0, a[n - 1] - a[0]);
    writeln!(out, "{}.{}", ans >> 1, (ans & 1) * 5).ok();
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    let t = sc.next::<usize>();
    for _ in 0..t {
        run(&mut sc, &mut out);
    }
}
