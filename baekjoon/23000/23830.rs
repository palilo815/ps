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
    let n = sc.next::<usize>();
    let a = sc.next_vec::<i32>(n);
    let p = sc.next::<i32>();
    let q = sc.next::<i32>();
    let r = sc.next::<i32>();
    let s = sc.next::<i64>();
    let f = |k: i32| -> bool {
        a.iter().fold(0, |sum, &x| {
            sum + if x > k + r {
                x - p
            } else if x < k {
                x + q
            } else {
                x
            } as i64
        }) >= s
    };
    let mut lo = 1;
    let mut hi = 100_002;
    while lo != hi {
        let m = lo + (hi - lo) / 2;
        if f(m) {
            hi = m;
        } else {
            lo = m + 1;
        }
    }
    writeln!(out, "{}", if lo == 100_002 { -1 } else { lo }).ok();
}
