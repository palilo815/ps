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

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let grid = (0..n).map(|_| sc.read_vec::<u32>(m)).collect::<Vec<_>>();
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let mut win = vec![vec![0; m]; n];
    let mut ans = 0;
    for (dx, dy) in MOVE {
        win.iter_mut().flatten().for_each(|x| *x = 1);
        for x in 0..n {
            for y in 0..m {
                let num = grid[x][y];
                let mut x = x + dx;
                let mut y = y + dy;
                while x < n && y < m {
                    if grid[x][y] <= num {
                        win[x][y] = 0;
                    }
                    x += dx;
                    y += dy;
                }
            }
        }
        ans += win.iter().flatten().sum::<u32>();
    }
    writeln!(bw, "{ans}").ok();
}
