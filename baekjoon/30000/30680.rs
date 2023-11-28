use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    const M: usize = 100_000;
    let mut edges = vec![(0, 0); M - 1];
    let mut values = vec![0; 2 * (M - 1)];
    let mut pref = vec![0; M + 1];
    let mut dist = vec![-1; M];
    let n = sc.read::<usize>();
    let mut stack = Vec::with_capacity(M);
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(std::cmp::Reverse(0));
    for _ in 0..n {
        let m = sc.read::<usize>();
        let edges = &mut edges[..m - 1];
        let values = &mut values[..2 * (m - 1)];
        let pref = &mut pref[..m + 1];
        let dist = &mut dist[..m];
        pref.fill(0);
        for e in edges.iter_mut() {
            e.0 = sc.read::<usize>() - 1;
            e.1 = sc.read::<usize>() - 1;
            pref[e.0] += 1;
            pref[e.1] += 1;
        }
        for i in 0..m {
            pref[i + 1] += pref[i];
        }
        for &(u, v) in edges.iter() {
            pref[u] -= 1;
            values[pref[u]] = v;
            pref[v] -= 1;
            values[pref[v]] = u;
        }
        dist.fill(-1);
        dist[0] = 0;
        stack.clear();
        stack.push(0);
        let offset = pq.pop().unwrap().0 + 1;
        for i in 0..m {
            let u = stack[i];
            let mut is_leaf = true;
            for &v in values[pref[u]..pref[u + 1]].iter() {
                if dist[v] == -1 {
                    dist[v] = dist[u] + 1;
                    is_leaf = false;
                    stack.push(v);
                }
            }
            if is_leaf {
                pq.push(std::cmp::Reverse(offset + dist[u]));
            }
        }
    }
    writeln!(out, "{}", pq.into_iter().min().unwrap().0).ok();
}
