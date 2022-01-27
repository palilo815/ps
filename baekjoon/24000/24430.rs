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
    let mut grid = (0..n)
        .map(|_| (0..n).map(|_| sc.next::<u32>() << 12).collect::<Vec<_>>())
        .collect::<Vec<_>>();
    let p = sc.next::<usize>();
    for _ in 0..p {
        grid[sc.next::<usize>() - 1][sc.next::<usize>() - 1] |= 1;
    }
    let mut dp = vec![0; n + 1];
    for i in 0..n {
        for j in 0..n {
            dp[j + 1] = dp[j].max(dp[j + 1]) + grid[i][j];
        }
    }
    writeln!(out, "{} {}", dp[n] >> 12, dp[n] & 0xfff).ok();
}
