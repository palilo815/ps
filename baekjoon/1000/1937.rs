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

struct Grid<T> {
    n: usize,
    m: usize,
    data: Box<[T]>,
}

impl<T> std::ops::Index<(usize, usize)> for Grid<T> {
    type Output = T;
    fn index(&self, (x, y): (usize, usize)) -> &Self::Output {
        &self.data[x * self.m + y]
    }
}

impl<T> std::ops::IndexMut<(usize, usize)> for Grid<T> {
    fn index_mut(&mut self, (x, y): (usize, usize)) -> &mut Self::Output {
        &mut self.data[x * self.m + y]
    }
}

impl<T: Clone + Copy> Grid<T> {
    fn new(n: usize, m: usize, default: T) -> Self {
        let data = vec![default; n * m].into_boxed_slice();
        Self { n, m, data }
    }
}

fn f(grid: &Grid<u32>, dp: &mut Grid<u32>, x: usize, y: usize) -> u32 {
    if dp[(x, y)] != 0 {
        return dp[(x, y)];
    }
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let mut val = 1;
    for &(dx, dy) in MOVE.iter() {
        let xx = x + dx;
        let yy = y + dy;
        if xx < grid.n && yy < grid.m && grid[(x, y)] > grid[(xx, yy)] {
            val = val.max(f(grid, dp, xx, yy) + 1);
        }
    }
    dp[(x, y)] = val;
    val
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut grid = Grid::new(n, n, 0);
    for x in grid.data.iter_mut() {
        *x = sc.read::<u32>();
    }
    let mut dp = Grid::new(n, n, 0);
    let mut ans = 0;
    for i in 0..n {
        for j in 0..n {
            ans = ans.max(f(&grid, &mut dp, i, j));
        }
    }
    writeln!(bw, "{ans}").ok();
}
