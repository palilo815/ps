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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
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
    let q = sc.read::<usize>();
    let mut grid = (0..n).map(|_| sc.read_vec::<u16>(m)).collect::<Vec<_>>();
    for _ in 0..q {
        if sc.read::<char>() == '0' {
            let i = sc.read::<usize>();
            let j = sc.read::<usize>();
            let k = sc.read::<u16>();
            grid[i][j] = k;
        } else {
            let i = sc.read::<usize>();
            let j = sc.read::<usize>();
            grid.swap(i, j);
        }
    }
    for row in grid {
        for x in row {
            write!(out, "{x} ").ok();
        }
        writeln!(out).ok();
    }
}
