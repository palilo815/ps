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
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut grid = (0..n).map(|_| sc.read_bytes()).collect::<Vec<_>>();
    let mut stack = Vec::new();
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let mut ans = 0;
    for i in 0..n {
        for j in 0..m {
            if grid[i][j] == b'.' {
                ans += 1;
                grid[i][j] = b'#';
                stack.push((i, j));
                while let Some((x, y)) = stack.pop() {
                    for &(dx, dy) in MOVE.iter() {
                        let xx = x + dx;
                        let yy = y + dy;
                        if xx != usize::MAX
                            && xx != n
                            && yy != usize::MAX
                            && yy != m
                            && grid[xx][yy] == b'.'
                        {
                            stack.push((xx, yy));
                            grid[xx][yy] = b'#';
                        }
                    }
                }
            }
        }
    }
    writeln!(out, "{}", ans).ok();
}
