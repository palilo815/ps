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
    let l = sc.read::<u32>();
    let mut adj = vec![vec![]; n];
    let mut rev = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        let w = sc.read::<u32>();
        adj[u].push((w, v));
        rev[v].push((w, u));
    }
    let mut pq = std::collections::BinaryHeap::new();
    let mut pq2 = std::collections::BinaryHeap::new();
    pq2.push(HeapNode(0, 0));
    const INF: u32 = 0x3f3f3f3f;
    let mut dist = vec![0; n];
    let mut dist2 = vec![INF; n];
    dist2[0] = 0;
    for cnt in 0..=n {
        std::mem::swap(&mut pq, &mut pq2);
        std::mem::swap(&mut dist, &mut dist2);
        dist2.fill(INF);
        while let Some(HeapNode(d, u)) = pq.pop() {
            if d != dist[u] {
                continue;
            }
            if u == n - 1 {
                writeln!(out, "{cnt}").ok();
                return;
            }
            for &(w, v) in adj[u].iter() {
                let d = d + w;
                if d <= l && dist[v] > d {
                    dist[v] = d;
                    pq.push(HeapNode(d, v));
                }
            }
            for &(w, v) in rev[u].iter() {
                let d = d + w;
                if d <= l && dist2[v] > d {
                    dist2[v] = d;
                    pq2.push(HeapNode(d, v));
                }
            }
        }
    }
    writeln!(out, "-1").ok();
}
