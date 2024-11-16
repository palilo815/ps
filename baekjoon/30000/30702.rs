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
    fn read_chars(&mut self) -> Vec<char> {
        self.it.next().unwrap().chars().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut a = (0..n).map(|_| sc.read_chars()).collect::<Vec<_>>();
    let b = (0..n).map(|_| sc.read_chars()).collect::<Vec<_>>();
    let mut stack = vec![];
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    const EMPTY: char = '\x00';
    for i in 0..n {
        for j in 0..m {
            if a[i][j] == EMPTY {
                continue;
            }
            let x = std::mem::replace(&mut a[i][j], EMPTY);
            let y = b[i][j];
            stack.push((i, j));
            while let Some((i, j)) = stack.pop() {
                for &(di, dj) in MOVE.iter() {
                    let ii = i + di;
                    let jj = j + dj;
                    if ii < n && jj < m && a[ii][jj] == x {
                        if b[ii][jj] != y {
                            writeln!(bw, "NO").ok();
                            return;
                        }
                        a[ii][jj] = EMPTY;
                        stack.push((ii, jj));
                    }
                }
            }
        }
    }
    writeln!(bw, "YES").ok();
}
