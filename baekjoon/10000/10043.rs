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
}

#[derive(Eq, PartialEq)]
struct HeapNode(u32, usize);

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
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let taxi = (0..n)
        .map(|_| (sc.read::<u32>(), sc.read::<u32>()))
        .collect::<Vec<_>>();
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut dist = vec![u32::MAX; n];
    let mut cost = vec![u32::MAX; n];
    let mut dq = std::collections::VecDeque::new();
    let mut pq = std::collections::BinaryHeap::new();
    cost[0] = 0;
    pq.push(HeapNode(0, 0));
    while let Some(HeapNode(c, u)) = pq.pop() {
        if c != cost[u] {
            continue;
        }
        let lim = taxi[u].1;
        dist.fill(u32::MAX);
        dist[u] = 0;
        dq.push_front(u);
        while let Some(u) = dq.pop_front() {
            if dist[u] == lim {
                continue;
            }
            for &v in adj[u].iter() {
                if dist[v] == u32::MAX {
                    dist[v] = dist[u] + 1;
                    dq.push_back(v);
                }
            }
        }
        let w = taxi[u].0;
        for (v, _) in dist.iter().enumerate().filter(|(_, &d)| d != u32::MAX) {
            if cost[v] > c + w {
                cost[v] = c + w;
                pq.push(HeapNode(c + w, v));
            }
        }
    }
    writeln!(out, "{}", cost[n - 1]).ok();
}
