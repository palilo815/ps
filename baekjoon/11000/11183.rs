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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let grid = (0..n).map(|_| sc.read_bytes()).collect::<Vec<_>>();
    let mut sea = vec![vec![false; m]; n];
    let mut stack = vec![];
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    for i in 0..n {
        for j in [0, m - 1] {
            if grid[i][j] == b'0' && !sea[i][j] {
                stack.push((i, j));
                sea[i][j] = true;
                while let Some((x, y)) = stack.pop() {
                    for &(dx, dy) in MOVE.iter() {
                        let xx = x + dx;
                        let yy = y + dy;
                        if xx < n && yy < m && grid[xx][yy] == b'0' && !sea[xx][yy] {
                            sea[xx][yy] = true;
                            stack.push((xx, yy));
                        }
                    }
                }
            }
        }
    }
    for j in 0..m {
        for i in [0, n - 1] {
            if grid[i][j] == b'0' && !sea[i][j] {
                stack.push((i, j));
                sea[i][j] = true;
                while let Some((x, y)) = stack.pop() {
                    for &(dx, dy) in MOVE.iter() {
                        let xx = x + dx;
                        let yy = y + dy;
                        if xx < n && yy < m && grid[xx][yy] == b'0' && !sea[xx][yy] {
                            sea[xx][yy] = true;
                            stack.push((xx, yy));
                        }
                    }
                }
            }
        }
    }
    let mut ans = 0;
    for x in 0..n {
        for y in 0..m {
            if grid[x][y] == b'1' {
                for &(dx, dy) in MOVE.iter() {
                    let xx = x + dx;
                    let yy = y + dy;
                    if xx >= n || yy >= m || sea[xx][yy] {
                        ans += 1;
                    }
                }
            }
        }
    }
    writeln!(bw, "{ans}").ok();
}
