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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

struct Grid<T> {
    n: usize,
    m: usize,
    data: Box<[T]>,
}

impl<T> std::ops::Index<usize> for Grid<T> {
    type Output = [T];
    fn index(&self, i: usize) -> &Self::Output {
        &self.data[i * self.m..(i + 1) * self.m]
    }
}

impl<T> std::ops::IndexMut<usize> for Grid<T> {
    fn index_mut(&mut self, i: usize) -> &mut Self::Output {
        &mut self.data[i * self.m..(i + 1) * self.m]
    }
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
    fn iter(&self) -> GridIter<'_, T> {
        GridIter { grid: self, x: 0, y: 0 }
    }
}

struct GridIter<'a, T> {
    grid: &'a Grid<T>,
    x: usize,
    y: usize,
}

impl<'a, T> Iterator for GridIter<'a, T> {
    type Item = ((usize, usize), &'a T);
    fn next(&mut self) -> Option<Self::Item> {
        if self.x == self.grid.n {
            return None;
        }
        let item = ((self.x, self.y), &self.grid[(self.x, self.y)]);
        if self.y + 1 == self.grid.m {
            self.x += 1;
            self.y = 0;
        } else {
            self.y += 1;
        }
        Some(item)
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut grid = Grid::new(n, m, 0);
    for i in 0..n {
        grid[i].copy_from_slice(sc.raw().as_bytes());
    }
    let (boss, _) = grid.iter().find(|x| *x.1 == b'B').unwrap();
    let mut dist = Grid::new(n, m, -1);
    dist[boss] = 0;
    let mut dq = std::collections::VecDeque::new();
    dq.push_back(boss);
    while let Some((x, y)) = dq.pop_front() {
        let d = dist[(x, y)];
        for &(dx, dy) in MOVE.iter() {
            let x = x + dx;
            let y = y + dy;
            if x < n && y < m && grid[x][y] != b'X' && dist[x][y] == -1 {
                dist[x][y] = d + 1;
                dq.push_back((x, y));
            }
        }
    }
    let mut dps = [0; 26];
    for _ in 0..k {
        let p = sc.read::<char>() as usize - b'a' as usize;
        dps[p] = sc.read::<i32>();
    }
    let mut pref = Vec::with_capacity(k);
    for (p, d) in grid.data.iter().zip(dist.data.iter()) {
        if p.is_ascii_lowercase() {
            let p = (*p - b'a') as usize;
            pref.push((*d, dps[p]));
        }
    }
    pref.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    let mut hp = sc.read::<i32>();
    let mut prev = 0;
    let mut total_dps = 0;
    for (i, (t, dps)) in pref.into_iter().enumerate() {
        hp -= total_dps * (t - prev);
        prev = t;
        total_dps += dps;
        if hp <= 0 {
            writeln!(bw, "{i}").ok();
            return;
        }
    }
    writeln!(bw, "{k}").ok();
}
