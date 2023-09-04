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

// return (n, root, sum_dist)
fn get_dist(sc: &mut Scanner) -> (usize, usize, usize) {
    let n = sc.read::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        let w = sc.read::<u32>();
        adj[u].push((w, v));
        adj[v].push((w, u));
    }
    let mut par = vec![usize::MAX; n];
    par[0] = 0;
    let mut topo = Vec::with_capacity(n);
    topo.push(0);
    for i in 0..n {
        let u = topo[i];
        for &(_, v) in adj[u].iter() {
            if par[v] == usize::MAX {
                par[v] = u;
                topo.push(v);
            }
        }
    }
    par[0] = usize::MAX;
    let half = ((n + 1) / 2) as u32;
    let mut root = 0;
    let mut sz = vec![0; n];
    for &u in topo.iter().rev() {
        sz[u] = adj[u].iter().fold(1, |acc, &(_, v)| acc + sz[v]);
        if sz[u] >= half {
            root = u;
            break;
        }
    }
    let mut dist = sz;
    dist.fill(u32::MAX);
    dist[root] = 0;
    let mut u = root;
    while par[u] != usize::MAX {
        let d = adj[u].iter().find(|&&(_, v)| v == par[u]).unwrap().0;
        dist[par[u]] = dist[u] + d;
        u = par[u];
    }
    for u in topo.into_iter() {
        for &(w, v) in adj[u].iter() {
            if dist[v] == u32::MAX {
                dist[v] = dist[u] + w;
            }
        }
    }
    (n, root, dist.into_iter().fold(0, |acc, d| acc + d as usize))
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let (n1, r1, d1) = get_dist(&mut sc);
    let (n2, r2, d2) = get_dist(&mut sc);
    writeln!(out, "{} {}", r1 + 1, r2 + 1).ok();
    writeln!(out, "{}", n1 * n2 + n1 * d2 + n2 * d1).ok();
}
