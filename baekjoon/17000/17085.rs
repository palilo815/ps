use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 15;
    let mut grid = [['.'; N + 2]; N + 2];
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    for row in grid.iter_mut().skip(1).take(n) {
        let s = sc.raw().chars();
        for (x, c) in row.iter_mut().skip(1).zip(s) {
            *x = c;
        }
    }
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let mut ans = i32::MIN;
    for i in 1..n + 1 {
        for j in 1..m + 1 {
            let mut points = [(i, j); 4];
            let mut cnt = 0;
            while points.iter().all(|&(x, y)| grid[x][y] == '#') {
                points.iter().for_each(|&(x, y)| grid[x][y] = '.');
                let area1 = cnt * 4 + 1;
                let mut area2 = i32::MIN;
                for i in 1..n + 1 {
                    for j in 1..m + 1 {
                        let mut points = [(i, j); 4];
                        let mut cnt = 0;
                        while points.iter().all(|&(x, y)| grid[x][y] == '#') {
                            cnt += 1;
                            for (p, d) in points.iter_mut().zip(MOVE) {
                                p.0 += d.0;
                                p.1 += d.1;
                            }
                        }
                        area2 = area2.max(cnt * 4 - 3);
                    }
                }
                ans = ans.max(area1 * area2);
                cnt += 1;
                for (p, d) in points.iter_mut().zip(MOVE) {
                    p.0 += d.0;
                    p.1 += d.1;
                }
            }
            points = [(i, j); 4];
            for _ in 0..cnt {
                points.iter().for_each(|&(x, y)| grid[x][y] = '#');
                for (p, d) in points.iter_mut().zip(MOVE) {
                    p.0 += d.0;
                    p.1 += d.1;
                }
            }
        }
    }
    writeln!(bw, "{ans}").ok();
}
