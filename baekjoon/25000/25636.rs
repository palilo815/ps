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
struct HeapNode(i64, i64, usize);

impl std::cmp::Ord for HeapNode {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0.cmp(&(self.0)).then(self.1.cmp(&rhs.1))
    }
}

impl std::cmp::PartialOrd for HeapNode {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let a = sc.read_vec::<i32>(n);
    let m = sc.read::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        let w = sc.read::<i32>();
        adj[u].push((w, v));
        adj[v].push((w, u));
    }
    let s = sc.read::<usize>() - 1;
    let t = sc.read::<usize>() - 1;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(HeapNode(0, a[s] as i64, s));
    const INF: i64 = 0x3f3f3f3f3f3f3f3f;
    let mut cost = vec![(INF, INF); n];
    cost[s] = (0, a[s] as i64);
    while let Some(HeapNode(d, l, u)) = pq.pop() {
        if (d, l) != cost[u] {
            continue;
        }
        for &(w, v) in adj[u].iter() {
            let d = d + w as i64;
            let l = l + a[v] as i64;
            if d < cost[v].0 || (d == cost[v].0 && l > cost[v].1) {
                cost[v] = (d, l);
                pq.push(HeapNode(d, l, v));
            }
        }
    }
    if cost[t].0 == INF {
        writeln!(out, "-1").ok();
    } else {
        writeln!(out, "{} {}", cost[t].0, cost[t].1).ok();
    }
}
