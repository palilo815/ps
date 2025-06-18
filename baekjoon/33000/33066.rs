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

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let s = sc.read::<usize>();
    let mut grid = Grid::new(n, m, 0);
    for x in grid.data.iter_mut() {
        *x = sc.read::<i32>();
    }
    let mut pref_row = Grid::new(n + 1, m, 0);
    for i in 0..n {
        for j in 0..m {
            pref_row[(i + 1, j)] = pref_row[(i, j)] + grid[(i, j)];
        }
    }
    let mut pref_col = Grid::new(n, m + 1, 0);
    for i in 0..n {
        for j in 0..m {
            pref_col[(i, j + 1)] = pref_col[(i, j)] + grid[(i, j)];
        }
    }
    let h = k.div_ceil(2);
    for i in (k..=n).step_by(s) {
        for j in (k..=m).step_by(s) {
            let row = pref_row[(i, j - h)] - pref_row[(i - k, j - h)];
            let col = pref_col[(i - h, j)] - pref_col[(i - h, j - k)];
            let x = grid[(i - h, j - h)] as i64;
            write!(bw, "{} ", row as i64 + col as i64 - x).ok();
        }
        writeln!(bw).ok();
    }
}
