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
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut grid = vec![vec![-1; m]; n];
    for _ in 0..k {
        let x = sc.read::<usize>() - 1;
        let y = sc.read::<usize>() - 1;
        let d = sc.read::<i32>();
        grid[x][y] = d;
    }
    for i in 0..n {
        for j in 0..m {
            if grid[i][j] != -1 {
                let d = grid[i][j] - 1;
                if i + 1 != n {
                    grid[i + 1][j] = grid[i + 1][j].max(d);
                }
                if j + 1 != m {
                    grid[i][j + 1] = grid[i][j + 1].max(d);
                }
            }
        }
    }
    for i in (0..n).rev() {
        for j in (0..m).rev() {
            if grid[i][j] != -1 {
                let d = grid[i][j] - 1;
                if i != 0 {
                    grid[i - 1][j] = grid[i - 1][j].max(d);
                }
                if j != 0 {
                    grid[i][j - 1] = grid[i][j - 1].max(d);
                }
            }
        }
    }
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let mut cur = vec![(0, 0)];
    let mut nxt = vec![];
    for ans in 0.. {
        if cur.is_empty() {
            writeln!(bw, "NO").ok();
            return;
        }
        nxt.clear();
        for &(x, y) in cur.iter() {
            if (x, y) == (n - 1, m - 1) {
                writeln!(bw, "YES\n{ans}").ok();
                return;
            }
            for &(dx, dy) in MOVE.iter() {
                let x = x + dx;
                let y = y + dy;
                if x == usize::MAX || x == n || y == usize::MAX || y == m || grid[x][y] != -1 {
                    continue;
                }
                if grid[x][y] == -1 {
                    grid[x][y] = 0;
                    nxt.push((x, y));
                }
            }
        }
        std::mem::swap(&mut cur, &mut nxt);
    }
}
