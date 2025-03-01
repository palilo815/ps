use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut grid = (0..n).map(|_| (sc.read_vec::<i32>(n))).collect::<Vec<_>>();
    grid[n - 1][n - 1] = 0;
    let mut dp = vec![vec![false; n]; n];
    dp[0][0] = true;
    for i in 0..n {
        for j in 0..n {
            if !dp[i][j] {
                continue;
            }
            let d = grid[i][j] as usize;
            if j + d < n {
                dp[i][j + d] = true;
            }
            if i + d < n {
                dp[i + d][j] = true;
            }
        }
    }
    writeln!(bw, "{}", if dp[n - 1][n - 1] { "HaruHaru" } else { "Hing" }).ok();
}
