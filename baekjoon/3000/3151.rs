use std::io::Write;

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
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let mut dp1 = [0; 20001];
    let mut dp2 = [0; 40001];
    let mut ans = 0;
    for _ in 0..n {
        let x = (sc.next::<isize>() + 10000) as usize;
        ans += dp2[30000 - x] as u64;
        for (dp2, dp1) in dp2.iter_mut().skip(x).zip(dp1.iter()) {
            *dp2 += *dp1;
        }
        dp1[x] += 1;
    }
    writeln!(out, "{}", ans).ok();
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
