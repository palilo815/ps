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
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut grid = (0..n).map(|_| sc.read_vec::<i32>(m)).collect::<Vec<_>>();
    for row in grid.iter_mut() {
        for x in row {
            *x -= sc.read::<i32>();
        }
    }
    let mut id = vec![vec![usize::MAX; m]; n];
    for _ in 0..k {
        let x = sc.read::<usize>() - 1;
        let y = sc.read::<usize>() - 1;
        if grid[x][y] != 0 {
            writeln!(bw, "No").ok();
            return;
        }
        id[x][y] = usize::MAX - 1;
    }
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let mut stack = vec![];
    let mut i = 0;
    for x in 0..n {
        for y in 0..m {
            if id[x][y] == usize::MAX {
                id[x][y] = i;
                stack.push((x, y));
                while let Some((x, y)) = stack.pop() {
                    for &(dx, dy) in MOVE.iter() {
                        let x = x + dx;
                        let y = y + dy;
                        if x < n && y < m && id[x][y] == usize::MAX {
                            id[x][y] = i;
                            stack.push((x, y));
                        }
                    }
                }
                i += 1;
            }
        }
    }
    let mut sum = vec![0; i];
    for x in 0..n {
        for y in 0..m {
            if id[x][y] != usize::MAX - 1 {
                sum[id[x][y]] += if (x ^ y) & 1 == 0 { grid[x][y] } else { -grid[x][y] } as i64;
            }
        }
    }
    let yes = sum.into_iter().all(|x| x == 0);
    writeln!(bw, "{}", if yes { "Yes" } else { "No" }).ok();
}
