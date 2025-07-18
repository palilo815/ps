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
    let p1 = grid.iter().flatten().filter(|&&x| x == b'P').count();
    let s = grid.iter().flatten().position(|&x| x == b'I').unwrap();
    let s = (s / m, s % m);
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let mut stack = vec![s];
    while let Some((x, y)) = stack.pop() {
        for &(dx, dy) in MOVE.iter() {
            let x = x + dx;
            let y = y + dy;
            if x < n && y < m && grid[x][y] != b'X' {
                grid[x][y] = b'X';
                stack.push((x, y));
            }
        }
    }
    let p2 = grid.iter().flatten().filter(|&&x| x == b'P').count();
    if p1 - p2 == 0 {
        writeln!(bw, "TT").ok();
    } else {
        writeln!(bw, "{}", p1 - p2).ok();
    }
}
