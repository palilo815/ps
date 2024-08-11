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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

struct DisjointSet {
    p: Box<[i32]>,
    dead: Box<[bool]>,
}

impl DisjointSet {
    fn new(n: usize) -> Self {
        Self { p: vec![-1; n].into(), dead: vec![false; n].into() }
    }
    fn find(&mut self, u: usize) -> usize {
        if self.p[u] < 0 {
            u
        } else {
            let rt = self.find(self.p[u] as usize);
            self.p[u] = rt as i32;
            rt
        }
    }
    fn unite(&mut self, u: usize, v: usize) {
        let mut u = self.find(u);
        let mut v = self.find(v);
        if u == v {
            return;
        }
        if self.p[u] > self.p[v] {
            std::mem::swap(&mut u, &mut v);
        }
        self.dead[u] |= self.dead[v];
        self.p[u] += self.p[v];
        self.p[v] = u as i32;
    }
    fn kill(&mut self, u: usize) {
        self.dead[self.find(u)] = true;
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let grid = (0..n).map(|_| sc.read_vec::<i32>(m)).collect::<Vec<_>>();
    let mut dsu = DisjointSet::new(n * m);
    for i in 0..n {
        for j in 0..m {
            if i + 1 != n {
                match grid[i][j].cmp(&grid[i + 1][j]) {
                    std::cmp::Ordering::Less => dsu.kill(i * m + j),
                    std::cmp::Ordering::Greater => dsu.kill((i + 1) * m + j),
                    _ => dsu.unite(i * m + j, (i + 1) * m + j),
                }
            }
            if j + 1 != m {
                match grid[i][j].cmp(&grid[i][j + 1]) {
                    std::cmp::Ordering::Less => dsu.kill(i * m + j),
                    std::cmp::Ordering::Greater => dsu.kill(i * m + j + 1),
                    _ => dsu.unite(i * m + j, i * m + j + 1),
                }
            }
        }
    }
    let ans = grid
        .into_iter()
        .flatten()
        .zip(dsu.p.iter())
        .zip(dsu.dead.iter())
        .filter(|((h, root), dead)| *h > 1 && root.is_negative() && !**dead)
        .count();
    writeln!(bw, "{ans}").ok();
}
