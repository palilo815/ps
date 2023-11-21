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

fn f(grid: &mut Vec<Vec<u8>>, i: usize, j: usize, n: u32) {
    if n == 0 {
        grid[i][j] = b'*';
        return;
    }
    let l = 5_usize.pow(n - 1);
    f(grid, i + 0 * l, j + 2 * l, n - 1);
    f(grid, i + 1 * l, j + 2 * l, n - 1);
    f(grid, i + 2 * l, j + 0 * l, n - 1);
    f(grid, i + 2 * l, j + 1 * l, n - 1);
    f(grid, i + 2 * l, j + 2 * l, n - 1);
    f(grid, i + 2 * l, j + 3 * l, n - 1);
    f(grid, i + 2 * l, j + 4 * l, n - 1);
    f(grid, i + 3 * l, j + 1 * l, n - 1);
    f(grid, i + 3 * l, j + 2 * l, n - 1);
    f(grid, i + 3 * l, j + 3 * l, n - 1);
    f(grid, i + 4 * l, j + 1 * l, n - 1);
    f(grid, i + 4 * l, j + 3 * l, n - 1);
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<u32>();
    let mut grid = vec![vec![b' '; 5_usize.pow(n)]; 5_usize.pow(n)];
    f(&mut grid, 0, 0, n);
    for x in grid {
        writeln!(out, "{}", String::from_utf8(x).unwrap()).ok();
    }
}
