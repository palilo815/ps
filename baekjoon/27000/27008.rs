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
    let c = sc.read::<usize>();
    let t = sc.read::<u32>();
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        let w = sc.read::<u32>();
        adj[u].push((w, v));
        adj[v].push((w, u));
    }
    const INF: u32 = 0x3f3f3f3f;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(HeapNode(0, 0));
    let mut dist = vec![INF; n];
    dist[0] = 0;
    while let Some(HeapNode(d, u)) = pq.pop() {
        if d != dist[u] {
            continue;
        }
        for &(w, v) in adj[u].iter() {
            let d = d + w;
            if dist[v] > d {
                dist[v] = d;
                pq.push(HeapNode(d, v));
            }
        }
    }
    let res = (0..c).map(|_| dist[sc.read::<usize>() - 1] <= t).collect::<Vec<_>>();
    writeln!(out, "{}", res.iter().filter(|&&x| x).count()).ok();
    for i in res.into_iter().enumerate().filter_map(|x| if x.1 { Some(x.0) } else { None }) {
        writeln!(out, "{}", i + 1).ok();
    }
}
