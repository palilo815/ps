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
    const N: usize = 1024;
    let mut grid = vec![vec![0; N]; N];
    let mut visited = vec![vec![false; N]; N];
    let mut stack = vec![];
    loop {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        let s = sc.read::<u32>();
        let l = sc.read::<u32>();
        if n == 0 {
            break;
        }
        for row in grid.iter_mut().take(n) {
            for x in row.iter_mut().take(m) {
                let r = sc.read::<u32>();
                let g = sc.read::<u32>();
                let b = sc.read::<u32>();
                *x = (r / s) << 16 | (g / s) << 8 | (b / s);
            }
        }
        visited.iter_mut().take(n).for_each(|v| v[..m].fill(false));
        let mut ans = 0;
        for i in 0..n {
            for j in 0..m {
                if visited[i][j] {
                    continue;
                }
                stack.push((i, j));
                visited[i][j] = true;
                let mut size = 0;
                while let Some((x, y)) = stack.pop() {
                    size += 1;
                    let cur = grid[x][y];
                    for dx in -1..=1 {
                        for dy in -1..=1 {
                            let x = (x as isize + dx) as usize;
                            let y = (y as isize + dy) as usize;
                            if x < n && y < m && !visited[x][y] && cur == grid[x][y] {
                                visited[x][y] = true;
                                stack.push((x, y));
                            }
                        }
                    }
                }
                ans += (size >= l) as i32;
            }
        }
        writeln!(bw, "{ans}").ok();
    }
}
