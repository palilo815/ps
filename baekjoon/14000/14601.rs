use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn f(grid: &mut [[i32; 128]], num: &mut i32, x: usize, y: usize, len: usize, hx: usize, hy: usize) {
    if len == 1 {
        return;
    }
    *num += 1;
    let tile = *num;
    let half = len / 2;
    let sub = [(x, y), (x, y + half), (x + half, y), (x + half, y + half)];
    for (subx, suby) in sub {
        if subx <= hx && hx < subx + half && suby <= hy && hy < suby + half {
            f(grid, num, subx, suby, half, hx, hy);
        } else {
            let hx = if subx == x { x + half - 1 } else {subx};
            let hy = if suby == y { y + half - 1 } else {suby};
            grid[hx][hy] = tile;
            f(grid, num, subx, suby, half, hx, hy);
        }
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = 2_usize.pow(sc.read());
    let y = sc.read::<usize>() - 1;
    let x = n - sc.read::<usize>();
    let mut grid = [[0; 128]; 128];
    grid[x][y] = -1;
    f(&mut grid, &mut 0, 0, 0, n, x, y);
    for row in grid.into_iter().take(n) {
        for x in row.into_iter().take(n) {
            write!(out, "{x} ").ok();
        }
        writeln!(out).ok();
    }
}
