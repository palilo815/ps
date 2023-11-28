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
    let n = sc.read::<usize>();
    let k = sc.read::<i64>();
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        let w = sc.read::<i64>();
        adj[u].push((v, w));
        adj[v].push((u, w));
    }
    let mut topo = Vec::with_capacity(n);
    topo.push(0);
    for i in 0..n {
        let u = topo[i];
        for (v, _) in adj[u].clone() {
            let j = adj[v].iter().position(|x| x.0 == u).unwrap();
            adj[v].swap_remove(j);
            topo.push(v);
        }
    }
    let mut dp = vec![std::collections::BinaryHeap::new(); n];
    let mut offset = vec![0; n];
    let mut ans = 1;
    for u in topo.into_iter().rev() {
        if adj[u].is_empty() {
            dp[u].push(0);
            continue;
        }
        let heavy = adj[u].iter().max_by(|l, r| dp[l.0].len().cmp(&dp[r.0].len())).unwrap();
        offset[u] = offset[heavy.0] + heavy.1;
        dp.swap(u, heavy.0);
        dp[u].push(-offset[u]);
        for (v, w) in std::mem::take(&mut adj[u]) {
            for x in std::mem::take(&mut dp[v]) {
                dp[u].push(x + offset[v] + w - offset[u]);
            }
        }
        while dp[u].peek().unwrap() + offset[u] > k {
            dp[u].pop();
        }
        ans = ans.max(dp[u].len());
    }
    writeln!(out, "{ans}").ok();
}
