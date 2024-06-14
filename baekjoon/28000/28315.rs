use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

#[derive(Eq, PartialEq)]
struct HeapNode(i64, usize);

impl std::cmp::Ord for HeapNode {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0.cmp(&(self.0))
    }
}

impl std::cmp::PartialOrd for HeapNode {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut edges = (0..m)
        .map(|_| {
            (
                sc.read::<usize>() - 1,
                sc.read::<usize>() - 1,
                sc.read::<i32>(),
                sc.read::<i32>(),
            )
        })
        .collect::<Vec<_>>();
    edges.sort_unstable_by(|l, r| l.2.cmp(&r.2).then(l.3.cmp(&r.3)));
    const INF: i64 = 0x3f3f3f3f3f3f3f3f;
    let mut pq = std::collections::BinaryHeap::with_capacity(m);
    let mut dist = vec![0; n];
    let mut adj = vec![vec![]; n];
    let mut ans = 0;
    for (u, v, l, p) in edges {
        dist.fill(INF);
        dist[u] = 0;
        pq.push(HeapNode(0, u));
        while let Some(HeapNode(d, u)) = pq.pop() {
            if d != dist[u] {
                continue;
            }
            for &(v, w) in adj[u].iter() {
                let d = d + w as i64;
                if dist[v] > d {
                    dist[v] = d;
                    pq.push(HeapNode(d, v));
                }
            }
        }
        if dist[v] > l as i64 {
            adj[u].push((v, l));
            adj[v].push((u, l));
            ans += p as i64;
        }
    }
    writeln!(bw, "{ans}").ok();
}
