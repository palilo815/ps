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
    let mut grid = (0..n).map(|_| sc.read_bytes()).collect::<Vec<_>>();
    let mut color = vec![vec![-1; m]; n];
    let mut stack = vec![];
    let mut sz = vec![];
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    for i in 0..n {
        for j in 0..m {
            if grid[i][j] == b'1' || color[i][j] != -1 {
                continue;
            }
            let id = sz.len() as i32;
            color[i][j] = id;
            stack.push((i, j));
            let mut area = 0;
            while let Some((x, y)) = stack.pop() {
                area += 1;
                for &(dx, dy) in MOVE.iter() {
                    let x = x + dx;
                    let y = y + dy;
                    if x < n && y < m && color[x][y] == -1 && grid[x][y] == b'0' {
                        color[x][y] = id;
                        stack.push((x, y));
                    }
                }
            }
            sz.push(area);
        }
    }
    let mut neighbors = vec![];
    for i in 0..n {
        for j in 0..m {
            if grid[i][j] == b'0' {
                continue;
            }
            for &(dx, dy) in MOVE.iter() {
                let x = i + dx;
                let y = j + dy;
                if x < n && y < m && color[x][y] != -1 && !neighbors.contains(&color[x][y]) {
                    neighbors.push(color[x][y]);
                }
            }
            let ans = neighbors.iter().fold(1, |acc, &i| acc + sz[i as usize]) % 10;
            neighbors.clear();
            grid[i][j] = b'0' + ans as u8;
        }
    }
    for row in grid {
        writeln!(bw, "{}", String::from_utf8(row).unwrap()).ok();
    }
}
