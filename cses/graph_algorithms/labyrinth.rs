use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    const DIR: [u8; 4] = [b'U', b'L', b'R', b'D'];
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut grid = (0..n).map(|_| sc.read_bytes()).collect::<Vec<_>>();
    let mut src = (0, 0);
    let mut dst = (0, 0);
    for i in 0..n {
        for j in 0..m {
            if grid[i][j] == b'A' {
                src = (i, j);
            } else if grid[i][j] == b'B' {
                dst = (i, j);
            }
        }
    }
    let mut deque = std::collections::VecDeque::new();
    deque.push_front(src);
    grid[src.0][src.1] = 0;
    grid[dst.0][dst.1] = b'.';
    while let Some((x, y)) = deque.pop_front() {
        for (&(dx, dy), &d) in MOVE.iter().zip(DIR.iter()) {
            let xx = x + dx;
            let yy = y + dy;
            if xx == usize::MAX || xx == n || yy == usize::MAX || yy == m || grid[xx][yy] != b'.' {
                continue;
            }
            deque.push_back((xx, yy));
            grid[xx][yy] = d;
        }
    }
    if grid[dst.0][dst.1] == b'.' {
        writeln!(out, "NO").ok();
        return;
    }
    let mut path = vec![];
    while src != dst {
        path.push(grid[dst.0][dst.1]);
        match grid[dst.0][dst.1] {
            b'U' => dst.0 += 1,
            b'L' => dst.1 += 1,
            b'R' => dst.1 -= 1,
            _ => dst.0 -= 1,
        }
    }
    path.reverse();
    writeln!(out, "YES").ok();
    writeln!(out, "{}", path.len()).ok();
    writeln!(out, "{}", String::from_utf8(path).unwrap()).ok();
}
