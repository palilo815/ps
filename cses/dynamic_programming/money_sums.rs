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
    let mut dp = [false; 100_001];
    dp[0] = true;
    for _ in 0..n {
        let x = sc.read::<usize>();
        for i in (x..100_001).rev() {
            dp[i] |= dp[i - x];
        }
    }
    dp[0] = false;
    writeln!(out, "{}", dp.iter().filter(|&&x| x).count()).ok();
    for (i, x) in dp.into_iter().enumerate() {
        // WARNING! compile error in CSES
        if x {
            write!(out, "{} ", i).ok();
        }
    }
}
