use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a String) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let t = sc.next::<u32>();
    for _ in 0..t {
        let n = sc.next::<usize>();
        let s = sc.next::<u32>();
        let mut a = sc.next_vec::<i32>(n);
        a.sort_unstable();
        let parametric = |mut lo, mut hi| {
            let f = |mid| -> bool {
                let mut prv = !0x3f3f3f3f;
                a.iter().fold(0, |acc, x| {
                    if *x - prv < mid {
                        acc
                    } else {
                        prv = *x;
                        acc + 1
                    }
                }) >= s
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
        writeln!(out, "{}", parametric(1, a[n - 1] - a[0])).ok();
    }
}
