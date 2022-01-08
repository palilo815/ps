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
    let a = sc.next::<i64>();
    let d = sc.next::<i64>();
    let q = sc.next::<usize>();
    for _ in 0..q {
        let t = sc.next::<char>();
        let l = sc.next::<i64>();
        let r = sc.next::<i64>();
        if t == '1' {
            writeln!(
                out,
                "{}",
                (r - l + 1) * (2 * (a + (l - 1) * d) + (r - l) * d) / 2
            )
            .ok();
        } else {
            let binary_gcd = |a: i64, b: i64| {
                if a == 0 || b == 0 {
                    return a | b;
                }
                let x = a.trailing_zeros();
                let y = b.trailing_zeros();
                let mut a = a >> x;
                let mut b = b >> y;
                while a != b {
                    let x = (a ^ b).trailing_zeros();
                    if a < b {
                        std::mem::swap(&mut a, &mut b);
                    }
                    a = (a - b) >> x;
                }
                a << x.min(y)
            };
            writeln!(
                out,
                "{}",
                binary_gcd(a + (l - 1) * d, if l == r { 0 } else { d })
            )
            .ok();
        }
    }
}
