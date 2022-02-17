use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
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
    let t = sc.next::<usize>();
    for _ in 0..t {
        run(&mut sc, &mut out);
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let mut a = sc.next_vec::<i32>(n);
    let mut ans = 0;
    for i in (0..n - 1).step_by(2) {
        let diff = a[i + 1] - a[i];
        if i + 2 < n {
            a[i + 1] -= diff;
            a[i + 2] -= diff;
        }
        if diff < 0 || a[i] != a[i + 1] {
            writeln!(out, "-1").ok();
            return;
        }
        ans += (diff as i64) << 1;
    }
    let x = *a.iter().min().unwrap() as i64;
    if x < 0 {
        writeln!(out, "-1").ok();
        return;
    }
    ans += a.into_iter().fold(0, |acc, y| acc - x + y as i64);
    writeln!(out, "{}", ans).ok();
}
