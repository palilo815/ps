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
struct HeapNode(u32, usize, usize);

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
    let k = sc.read::<usize>();
    let s = sc.read::<usize>() - 1;
    let t = sc.read::<usize>() - 1;
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        let w = sc.read::<usize>();
        adj[u].push((w, v));
    }
    let mut dist = vec![[u32::MAX; 50]; n];
    dist[s][0] = 0;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(HeapNode(0, s, 0));
    while let Some(HeapNode(d, u, rem)) = pq.pop() {
        if dist[u][rem] != d {
            continue;
        }
        for &(w, v) in adj[u].iter() {
            let rem = (rem + w) % k;
            if dist[v][rem] > d + w as u32 {
                dist[v][rem] = d + w as u32;
                pq.push(HeapNode(dist[v][rem], v, rem));
            }
        }
    }
    if dist[t][0] == u32::MAX {
        writeln!(out, "IMPOSSIBLE").ok();
    } else {
        writeln!(out, "{}", dist[t][0]).ok();
    }
}
