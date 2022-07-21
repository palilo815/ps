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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
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

#[derive(Eq, PartialEq)]
struct HeapNode(u32, usize);

impl std::cmp::Ord for HeapNode {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        self.0.cmp(&(rhs.0))
    }
}

impl std::cmp::PartialOrd for HeapNode {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let s = sc.read::<u32>();
    let a = sc.read_vec::<u32>(n);
    let mut best = vec![0; n];
    best[0] = s;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(HeapNode(s, 0));
    while let Some(HeapNode(d, u)) = pq.pop() {
        if best[u] != d {
            continue;
        }
        let d = if d > a[u] { d } else { d / 2 };
        for &v in adj[u].iter() {
            if d > best[v] {
                pq.push(HeapNode(d, v));
                best[v] = d;
            }
        }
    }
    if best[n - 1] <= a[n - 1] {
        best[n - 1] /= 2;
    }
    writeln!(out, "{}", best[n - 1]).ok();
}
