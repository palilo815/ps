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
struct HeapNode<T>(T, usize, usize);

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
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let s = (0..n).map(|_| sc.read_vec::<u32>(m)).collect::<Vec<_>>();
    let mut v = vec![vec![false; m]; n];
    let mut pq = std::collections::BinaryHeap::new();
    for y in 0..m {
        pq.push(HeapNode(s[0][y], 0, y));
        v[0][y] = true;
    }
    for x in 1..n {
        pq.push(HeapNode(s[x][0], x, 0));
        v[x][0] = true;
        if m > 1 {
            pq.push(HeapNode(s[x][m - 1], x, m - 1));
            v[x][m - 1] = true;
        }
    }
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    let mut ans = 0;
    for _ in 0..k {
        let HeapNode(w, x, y) = pq.pop().unwrap();
        ans = ans.max(w);
        for &(dx, dy) in MOVE.iter() {
            let x = x + dx;
            let y = y + dy;
            if x < n && y < m && !v[x][y] {
                pq.push(HeapNode(s[x][y], x, y));
                v[x][y] = true;
            }
        }
    }
    writeln!(bw, "{ans}").ok();
}
