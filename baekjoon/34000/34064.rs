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
        grid[x][y] = -2;
    }
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let mut num = 0;
    let mut stack = vec![];
    for i in 0..n {
        for j in 0..m {
            if grid[i][j] != -1 {
                continue;
            }
            stack.push((i, j));
            grid[i][j] = num;
            while let Some((x, y)) = stack.pop() {
                for &(dx, dy) in MOVE.iter() {
                    let x = x + dx;
                    let y = y + dy;
                    if x < n && y < m && grid[x][y] == -1 {
                        grid[x][y] = num;
                        stack.push((x, y));
                    }
                }
            }
            num += 1;
        }
    }
    let mut a = vec![0; num as usize];
    let x1 = sc.read::<usize>() - 1;
    let y1 = sc.read::<usize>() - 1;
    let x2 = sc.read::<usize>();
    let y2 = sc.read::<usize>();
    for x in x1..x2 {
        for y in y1..y2 {
            if grid[x][y] >= 0 {
                a[grid[x][y] as usize] += 1;
            }
        }
    }
    let mut b = vec![0; num as usize];
    let x1 = sc.read::<usize>() - 1;
    let y1 = sc.read::<usize>() - 1;
    let x2 = sc.read::<usize>();
    let y2 = sc.read::<usize>();
    for x in x1..x2 {
        for y in y1..y2 {
            if grid[x][y] >= 0 {
                b[grid[x][y] as usize] += 1;
            }
        }
    }
    let ans = a.into_iter().zip(b).fold(0_u64, |acc, (a, b)| acc + a * b);
    writeln!(bw, "{ans}").ok();
}
