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

#[derive(Eq, PartialEq)]
struct HeapNode<T>(T, usize, usize, usize);

impl<T: Ord> std::cmp::Ord for HeapNode<T> {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0.cmp(&(self.0))
    }
}

impl<T: Ord> std::cmp::PartialOrd for HeapNode<T> {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let grid = (0..n).map(|_| sc.read_vec::<i32>(m)).collect::<Vec<_>>();
    let mut dist = vec![vec![i32::MAX; m]; n];
    dist.iter_mut().for_each(|row| *row.last_mut().unwrap() = 0);
    let mut pq = (0..n).map(|i| HeapNode(0, i, m - 1, i)).collect::<std::collections::BinaryHeap<_>>();
    let mut ans = vec![0; n];
    while let Some(HeapNode(mut d, x, y, z)) = pq.pop() {
        if d > dist[x][y] {
            continue;
        }
        if y == 0 {
            ans[z] += 1;
        }
        d += grid[x][y];
        for &(dx, dy) in MOVE.iter() {
            let x = x + dx;
            let y = y + dy;
            if x < n && y < m && dist[x][y] > d {
                dist[x][y] = d;
                pq.push(HeapNode(d, x, y, z));
            }
        }
    }
    for x in ans {
        writeln!(bw, "{x}").ok();
    }
}
