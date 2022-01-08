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

use std::io::Write;

trait ChMinMax {
    fn chmin(&mut self, x: Self) -> bool;
    fn chmax(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChMinMax for T {
    fn chmin(&mut self, x: Self) -> bool {
        *self > x && {
            *self = x;
            true
        }
    }
    fn chmax(&mut self, x: Self) -> bool {
        *self < x && {
            *self = x;
            true
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
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let k = sc.next::<usize>();
    let mut grid = vec![vec![usize::MAX; m + 2]; n + 2];
    for i in 0..k {
        let x = sc.next::<usize>();
        let y = sc.next::<usize>();
        grid[x][y] = i;
    }
    let root = sc.next::<usize>() - 1;
    let s = grid.iter().flatten().position(|&x| x == root).unwrap();
    let s = (s / (m + 2), s % (m + 2));
    let mut q = std::collections::VecDeque::from([s]);
    let mut order = Vec::with_capacity(k);
    let mut par = vec![usize::MAX; k];
    let mut dist = vec![vec![-1; m + 2]; n + 2];
    dist[s.0][s.1] = 0;
    while let Some((x, y)) = q.pop_front() {
        order.push(grid[x][y]);
        for xx in x - 1..=x + 1 {
            for yy in y - 1..=y + 1 {
                if grid[xx][yy] == usize::MAX {
                    continue;
                }
                if dist[xx][yy] == -1 {
                    dist[xx][yy] = dist[x][y] + 1;
                    par[grid[xx][yy]] = grid[x][y];
                    q.push_back((xx, yy));
                } else if dist[xx][yy] == dist[x][y] + 1 {
                    par[grid[xx][yy]].chmin(grid[x][y]);
                }
            }
        }
    }
    if par.iter().filter(|&&x| x == usize::MAX).count() != 1 {
        writeln!(out, "-1").ok();
        return;
    }
    order.reverse();
    order.pop();
    let mut sz = vec![1; k];
    for &u in order.iter() {
        sz[par[u]] += sz[u];
    }
    for &x in sz.iter() {
        write!(out, "{} ", x).ok();
    }
}
