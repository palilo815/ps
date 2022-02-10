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
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    const MAX_N: usize = 100_000;
    let mut y_val = [0; MAX_N];
    let t = sc.next::<usize>();
    for _ in 0..t {
        let n = sc.next::<usize>();
        for _ in 0..n {
            y_val[sc.next::<usize>() - 1] = sc.next::<u32>();
        }
        let ans = y_val
            .iter()
            .take(n)
            .fold(
                (0, u32::MAX),
                |acc, &x| {
                    if x > acc.1 {
                        acc
                    } else {
                        (acc.0 + 1, x)
                    }
                },
            )
            .0;
        writeln!(out, "{}", ans).ok();
    }
}
