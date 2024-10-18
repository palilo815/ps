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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let mut grid = [[0; 1000]; 1000];
    let mut dist = [[0; 1000]; 1000];
    let mut dq = std::collections::VecDeque::new();
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        for row in grid.iter_mut().take(n) {
            for x in row.iter_mut().take(m) {
                *x = sc.read::<i32>();
            }
        }
        dist.iter_mut().take(n).for_each(|row| row[..m].fill(-1));
        for y in 0..m {
            dist[0][y] = grid[0][y];
            dist[n - 1][y] = grid[n - 1][y];
            if grid[0][y] == 0 {
                dq.push_front((0, y));
            } else {
                dq.push_back((0, y));
            }
            if grid[n - 1][y] == 0 {
                dq.push_front((n - 1, y));
            } else {
                dq.push_back((n - 1, y));
            }
        }
        for x in 1..n - 1 {
            dist[x][0] = grid[x][0];
            dist[x][m - 1] = grid[x][m - 1];
            if grid[x][0] == 0 {
                dq.push_front((x, 0));
            } else {
                dq.push_back((x, 0));
            }
            if grid[x][m - 1] == 0 {
                dq.push_front((x, m - 1));
            } else {
                dq.push_back((x, m - 1));
            }
        }
        const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
        while let Some((x, y)) = dq.pop_front() {
            for &(dx, dy) in MOVE.iter() {
                let xx = x + dx;
                let yy = y + dy;
                if xx < n && yy < m && dist[xx][yy] == -1 {
                    dist[xx][yy] = dist[x][y] + grid[xx][yy];
                    if grid[xx][yy] == 0 {
                        dq.push_front((xx, yy));
                    } else {
                        dq.push_back((xx, yy));
                    }
                }
            }
        }
        let mut security = -1;
        let mut sections = 0;
        for x in 0..n {
            for y in 0..m {
                if grid[x][y] == 0 {
                    match dist[x][y].cmp(&security) {
                        std::cmp::Ordering::Greater => {
                            security = dist[x][y];
                            sections = 1;
                        }
                        std::cmp::Ordering::Equal => sections += 1,
                        _ => {}
                    }
                }
            }
        }
        writeln!(bw, "{security} {sections}").ok();
    }
}
