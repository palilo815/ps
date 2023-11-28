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

fn f(grid: &mut Vec<Vec<u8>>, i: usize, j: usize, n: usize) {
    if n == 3 {
        grid[i][j] = b'*';
        grid[i + 1][j - 1] = b'*';
        grid[i + 1][j + 1] = b'*';
        grid[i + 2][j - 2] = b'*';
        grid[i + 2][j - 1] = b'*';
        grid[i + 2][j] = b'*';
        grid[i + 2][j + 1] = b'*';
        grid[i + 2][j + 2] = b'*';
        return;
    }
    let n = n / 2;
    f(grid, i, j, n);
    f(grid, i + n, j - n, n);
    f(grid, i + n, j + n, n);
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let mut grid = vec![vec![b' '; 2 * n]; n];
    f(&mut grid, 0, n - 1, n);
    for s in grid {
        writeln!(out, "{}", String::from_utf8(s).unwrap()).ok();
    }
}
