use std::io::*;

struct Scanner<'sl> {
    it: std::str::SplitWhitespace<'sl>,
}

impl<'sl> Scanner<'sl> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

struct Csr<T> {
    values: Box<[(usize, T)]>,
    pref: Box<[usize]>,
}

impl<T> std::ops::Index<usize> for Csr<T> {
    type Output = [(usize, T)];
    fn index(&self, i: usize) -> &Self::Output {
        &self.values[self.pref[i]..self.pref[i + 1]]
    }
}

impl<T: Copy + Default> Csr<T> {
    fn from_direct_edges(n: usize, edges: Vec<(usize, usize, T)>) -> Self {
        let mut values = vec![(0, T::default()); edges.len()].into_boxed_slice();
        let mut pref = vec![0; n + 1].into_boxed_slice();
        for &(u, _, _) in edges.iter() {
            pref[u] += 1;
        }
        for i in 0..n {
            pref[i + 1] += pref[i];
        }
        for (u, v, w) in edges {
            pref[u] -= 1;
            values[pref[u]] = (v, w);
        }
        Self { values, pref }
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
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>() - 1;
    let mut edges = vec![];
    edges.extend((0..n).map(|i| (n + i, 3 * n + i, 0)));
    for i in 1..n {
        edges.push((i, 2 * i, 0));
        edges.push((i, 2 * i + 1, 0));
        edges.push((2 * n + 2 * i, 2 * n + i, 0));
        edges.push((2 * n + 2 * i + 1, 2 * n + i, 0));
    }
    for i in 4 * n..4 * n + m {
        let w = sc.read::<i64>();
        let mut sl = n + sc.read::<usize>() - 1;
        let mut sr = n + sc.read::<usize>();
        let mut dl = n + sc.read::<usize>() - 1;
        let mut dr = n + sc.read::<usize>();
        while dl != dr {
            if dl & 1 == 1 {
                edges.push((i, dl, 0));
                dl += 1;
            }
            if dr & 1 == 1 {
                dr -= 1;
                edges.push((i, dr, 0));
            }
            dl >>= 1;
            dr >>= 1;
        }
        while sl != sr {
            if sl & 1 == 1 {
                edges.push((2 * n + sl, i, w));
                sl += 1;
            }
            if sr & 1 == 1 {
                sr -= 1;
                edges.push((2 * n + sr, i, w));
            }
            sl >>= 1;
            sr >>= 1;
        }
    }
    let csr = Csr::from_direct_edges(4 * n + m, edges);
    const INF: i64 = 0x3f3f3f3f3f3f3f3f;
    let mut dist = vec![INF; 4 * n + m];
    dist[k + n] = 0;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(HeapNode(0, k + n));
    while let Some(HeapNode(d, u)) = pq.pop() {
        if d != dist[u] {
            continue;
        }
        for &(v, w) in csr[u].iter() {
            let d = d + w;
            if dist[v] > d {
                dist[v] = d;
                pq.push(HeapNode(d, v));
            }
        }
    }
    for x in dist.into_iter().skip(3 * n).take(n) {
        write!(out, "{} ", if x == INF { -1 } else { x }).ok();
    }
}
