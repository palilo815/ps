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
    let m = sc.next::<usize>();
    let mut dp = vec![i32::MIN; m + 1];
    dp[0] = 0;
    for _ in 0..n {
        let s = sc.next::<i32>();
        let p = sc.next::<usize>();
        for i in (0..=m).rev() {
            let win = if i > p && dp[i - p - 1] != i32::MIN {
                dp[i - p - 1] + s
            } else {
                i32::MIN
            };
            let draw = if i >= p && dp[i - p] != i32::MIN {
                dp[i - p]
            } else {
                i32::MIN
            };
            let lose = if dp[i] == i32::MIN {
                i32::MIN
            } else {
                dp[i] - s
            };
            dp[i] = std::cmp::max(win, std::cmp::max(draw, lose));
        }
    }
    writeln!(
        out,
        "{}",
        if dp.iter().find(|&&x| x > 0).is_some() {
            'W'
        } else if dp.contains(&0) {
            'D'
        } else {
            'L'
        }
    )
    .ok();
}
