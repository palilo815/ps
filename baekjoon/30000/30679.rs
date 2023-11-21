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

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut grid = [[0; 100]; 100];
    for i in 0..n {
        for j in 0..m {
            grid[i][j] = sc.read::<usize>();
        }
    }
    const MOVE: [(usize, usize); 4] = [(0, 1), (1, 0), (0, usize::MAX), (usize::MAX, 0)];
    let mut is_out = vec![false; n];
    let mut visited = [[[usize::MAX; 4]; 100]; 100];
    let mut check = |i: usize| {
        let mut x = i;
        let mut y = 0;
        let mut d = 0;
        loop {
            if visited[x][y][d] != usize::MAX {
                is_out[i] = is_out[visited[x][y][d]];
                break;
            }
            visited[x][y][d] = i;
            let l = grid[x][y];
            x += MOVE[d].0 * l;
            y += MOVE[d].1 * l;
            d = (d + 1) & 3;
            if x >= n || y >= m {
                is_out[i] = true;
                break;
            }
        }
    };
    for i in 0..n {
        check(i);
    }
    writeln!(out, "{}", is_out.iter().filter(|&&x| !x).count()).ok();
    for i in 0..n {
        if !is_out[i] {
            write!(out, "{} ", i + 1).ok();
        }
    }
}
