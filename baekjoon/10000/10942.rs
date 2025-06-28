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

struct Grid<T> {
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
        Self { m, data }
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let a = sc.read_vec::<u32>(n);
    let mut dp = Grid::new(n, n + 1, false);
    for i in 0..n {
        dp[(i, i)] = true;
        dp[(i, i + 1)] = true;
    }
    for k in 2..=n {
        for i in k..=n {
            dp[(i - k, i)] = dp[(i - k + 1, i - 1)] & (a[i - k] == a[i - 1]);
        }
    }
    let m = sc.read::<usize>();
    for _ in 0..m {
        let l = sc.read::<usize>() - 1;
        let r = sc.read::<usize>();
        writeln!(bw, "{}", if dp[(l, r)] { "1" } else { "0" }).ok();
    }
}
