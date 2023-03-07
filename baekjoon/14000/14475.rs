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

#[derive(Eq, PartialEq)]
struct HeapNode(u32, usize, usize);

impl std::cmp::Ord for HeapNode {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0
            .cmp(&(self.0))
            .then((rhs.1).abs_diff(200).cmp(&(self.1).abs_diff(200)))
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
    let t = sc.read_vec::<u8>(n);
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        let w = sc.read::<u32>();
        adj[u].push((w, v));
        adj[v].push((w, u));
    }
    let mut dist = vec![[u32::MAX; 401]; n];
    dist[0][200 - k] = 0;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(HeapNode(0, 200 - k, 0));
    while let Some(HeapNode(d, left, u)) = pq.pop() {
        if dist[u][left] != d {
            continue;
        }
        for &(w, v) in adj[u].iter() {
            match t[v] {
                0 => {
                    if left <= 200 + w as usize && dist[v][200 - k] > d + w {
                        dist[v][200 - k] = d + w;
                        pq.push(HeapNode(d + w, 200 - k, v));
                    }
                }
                2 => {
                    if left + w as usize >= 200 && dist[v][200 + k] > d + w {
                        dist[v][200 + k] = d + w;
                        pq.push(HeapNode(d + w, 200 + k, v));
                    }
                }
                _ => {
                    let left = if left < 200 {
                        200.min(left + w as usize)
                    } else {
                        200.max(left - w as usize)
                    };
                    if dist[v][left] > d + w {
                        dist[v][left] = d + w;
                        pq.push(HeapNode(d + w, left, v));
                        if left >= 200 {
                            let mut i = left + 1;
                            while i != 401 && dist[v][i] > d + w {
                                dist[v][i] = d + w;
                                i += 1;
                            }
                        }
                        if left <= 200 {
                            let mut i = left - 1;
                            while i != usize::MAX && dist[v][i] > d + w {
                                dist[v][i] = d + w;
                                i -= 1;
                            }
                        }
                    }
                }
            }
        }
    }
    writeln!(out, "{}", dist[n - 1].iter().min().unwrap()).ok();
}
