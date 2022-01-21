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
    for tc in 1..=t {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();
        let mut grid = (0..n).map(|_| sc.next_vec::<u8>(m)).collect::<Vec<_>>();
        let mut dp = vec![vec![(0, 0); m]; n];
        let mut ans = 0;
        for t in 0..4 {
            if t & 1 == 1 {
                grid.reverse();
            } else if t == 2 {
                grid.iter_mut().for_each(|x| x.reverse());
            }
            for i in 0..n {
                for j in 0..m {
                    if grid[i][j] == 1 {
                        dp[i][j].0 = if i == 0 { 1 } else { dp[i - 1][j].0 + 1 };
                        dp[i][j].1 = if j == 0 { 1 } else { dp[i][j - 1].1 + 1 };
                    } else {
                        dp[i][j] = (0, 0);
                    }
                }
            }
            ans += dp.iter().flatten().fold(0, |acc, &(x, y)| {
                acc + 0.max(x.min(y >> 1) - 1) + 0.max(y.min(x >> 1) - 1)
            });
        }
        writeln!(out, "Case #{}: {}", tc, ans).ok();
    }
}
