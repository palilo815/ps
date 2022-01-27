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
    let mut grid = (0..n).map(|_| sc.next_vec::<i32>(n)).collect::<Vec<_>>();
    let p = sc.next::<usize>();
    let mut mid = vec![vec![false; n]; n];
    for _ in 0..p {
        mid[sc.next::<usize>() - 1][sc.next::<usize>() - 1] = true;
    }
    const INF: i32 = 0x3f3f3f3f;
    for dia in 1..(2 * (n - 1)) {
        let mut unreachable = false;
        let mut y = if dia < n { 0 } else { dia - n + 1 };
        let mut x = dia - y;
        while x != usize::MAX && y != n {
            if unreachable {
                grid[x][y] = !INF;
            }
            unreachable |= mid[x][y];
            x -= 1;
            y += 1;
        }
        let mut unreachable = false;
        let mut x = if dia < n { 0 } else { dia - n + 1 };
        let mut y = dia - x;
        while x != n && y != usize::MAX {
            if unreachable {
                grid[x][y] = !INF;
            }
            unreachable |= mid[x][y];
            x += 1;
            y -= 1;
        }
    }
    let mut dp = vec![!INF; n + 1];
    for i in 0..n {
        for j in 0..n {
            if (i, j) == (0, 0) {
                dp[1] = grid[0][0];
                continue;
            }
            dp[j + 1] = if grid[i][j] == !INF {
                !INF
            } else {
                dp[j].max(dp[j + 1]) + grid[i][j]
            };
        }
    }
    writeln!(out, "{}", dp[n].max(-1)).ok();
}
