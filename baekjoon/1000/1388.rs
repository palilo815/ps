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
    fn read_chars(&mut self) -> Vec<char> {
        self.it.next().unwrap().chars().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let grid = (0..n).map(|_| sc.read_chars()).collect::<Vec<_>>();
    let mut ans = 0;
    for i in 0..n {
        for j in 0..m {
            match grid[i][j] {
                '-' => ans += (j == 0 || grid[i][j - 1] != '-') as i32,
                '|' => ans += (i == 0 || grid[i - 1][j] != '|') as i32,
                _ => unreachable!(),
            }
        }
    }
    writeln!(bw, "{ans}").ok();
}
