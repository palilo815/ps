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
    let mut grid = [[0; 300]; 300];
    let t = sc.next::<u32>();
    for tc in 1..=t {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();
        for i in 0..n {
            for j in 0..m {
                grid[i][j] = sc.next::<u32>();
            }
        }
        let mut ans = 0;
        for i in 0..n {
            for j in 0..m {
                if i != 0 && grid[i][j] + 1 < grid[i - 1][j] {
                    ans += (grid[i - 1][j] - grid[i][j] - 1) as u64;
                    grid[i][j] = grid[i - 1][j] - 1;
                }
                if j != 0 && grid[i][j] + 1 < grid[i][j - 1] {
                    ans += (grid[i][j - 1] - grid[i][j] - 1) as u64;
                    grid[i][j] = grid[i][j - 1] - 1;
                }
            }
        }
        for i in (0..n).rev() {
            for j in (0..m).rev() {
                if i + 1 != n && grid[i][j] + 1 < grid[i + 1][j] {
                    ans += (grid[i + 1][j] - grid[i][j] - 1) as u64;
                    grid[i][j] = grid[i + 1][j] - 1;
                }
                if j + 1 != m && grid[i][j] + 1 < grid[i][j + 1] {
                    ans += (grid[i][j + 1] - grid[i][j] - 1) as u64;
                    grid[i][j] = grid[i][j + 1] - 1;
                }
            }
        }
        writeln!(out, "Case #{}: {}", tc, ans).ok();
    }
}
