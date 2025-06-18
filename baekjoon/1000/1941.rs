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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

const N: usize = 5;
const K: usize = 7;
const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];

fn dfs(check: &mut [[bool; N]; N], x: usize, y: usize) -> usize {
    if x >= N || y >= N || !std::mem::replace(&mut check[x][y], false) {
        return 0;
    }
    MOVE.iter().fold(1, |acc, &(dx, dy)| {
        let x = x + dx;
        let y = y + dy;
        acc + dfs(check, x, y)
    })
}

fn f(grid: &[i32; N * N], check: &mut [[bool; N]; N], s: usize, ally: usize, enemy: usize) -> i32 {
    if ally + enemy == K {
        let mut check = *check;
        return (dfs(&mut check, (s - 1) / N, (s - 1) % N) == K) as i32;
    }
    let mut acc = 0;
    let t = N * N - K + ally + enemy + 1;
    for i in s..t {
        if grid[i] == 1 {
            check[i / N][i % N] = true;
            acc += f(grid, check, i + 1, ally + 1, enemy);
            check[i / N][i % N] = false;
        } else if enemy < 3 {
            check[i / N][i % N] = true;
            acc += f(grid, check, i + 1, ally, enemy + 1);
            check[i / N][i % N] = false;
        }
    }
    acc
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let mut grid = [0; N * N];
    for c in grid.chunks_mut(N) {
        for (x, c) in c.iter_mut().zip(sc.raw().bytes()) {
            *x = (c == b'S') as i32;
        }
    }
    let ans = f(&grid, &mut [[false; N]; N], 0, 0, 0);
    writeln!(bw, "{ans}").ok();
}
