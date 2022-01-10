use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a String) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let k = sc.next::<usize>();
    let n = 1 << k;
    let mut grid = vec![vec![0_u32; n + 2]; n + 1];
    for i in 0..n {
        for j in 1..=n {
            grid[i][j] = sc.next::<u32>();
        }
    }
    let check_left = |x, y| grid[x][y] == grid[x + 1][y - 1] && grid[x][y] == grid[x + 1][y];
    let check_right = |x, y| {
        grid[x][y] == 2
        /*
        (grid[x][y] == grid[x][y + 1]) as u32
            + (grid[x][y] == grid[x + 1][y]) as u32
            + (grid[x][y] == grid[x + 1][y + 1]) as u32
            == 2
            */
    };
    let set_left = |x, y| {
        grid[x][y] = 0;
        grid[x + 1][y - 1] = 0;
        grid[x + 1][y] = 0;
    };
    let set_right = |x, y| {
        if grid[x][y] == grid[x][y + 1] {
            grid[x][y + 1] = 0;
        }
        if grid[x][y] == grid[x + 1][y] {
            grid[x + 1][y] = 0;
        }
        if grid[x][y] == grid[x + 1][y + 1] {
            grid[x + 1][y + 1] = 0;
        }
        grid[x][y] = 0;
    };
    let used = vec![false; ((1 << (2 * k)) - 1) / 3 + 1];
    for i in 0..n {
        for j in 1..=n {
            if grid[i][j] == 0 {
                continue;
            }
            if std::mem::replace(&mut used[grid[i][j] as usize], true) {
                writeln!(out, "0").ok();
                return;
            }
            if check_left(i, j) {
                set_left(i, j);
            } else if check_right(i, j) {
                set_right(i, j);
            } else {
                writeln!(out, "0").ok();
                return;
            }
        }
    }
    writeln!(out, "-1").ok();
}
