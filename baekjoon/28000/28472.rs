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
    let r = sc.read::<usize>() - 1;
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut topo = Vec::with_capacity(n);
    topo.push(r);
    for i in 0..n {
        let u = topo[i];
        for v in adj[u].clone() {
            let j = adj[v].iter().position(|&x| x == u).unwrap();
            adj[v].swap_remove(j);
        }
        topo.extend_from_slice(&adj[u]);
    }
    let mut state = vec![false; n];
    for &u in topo.iter() {
        for &v in adj[u].iter() {
            state[v] = !state[u];
        }
    }
    let mut dp = vec![0; n];
    for _ in 0..sc.read::<usize>() {
        let u = sc.read::<usize>() - 1;
        let x = sc.read::<u32>();
        dp[u] = x;
    }
    for &u in topo.iter().rev() {
        if adj[u].is_empty() {
            continue;
        }
        dp[u] = if state[u] {
            adj[u].iter().fold(u32::MAX, |acc, &v| acc.min(dp[v]))
        } else {
            adj[u].iter().fold(u32::MIN, |acc, &v| acc.max(dp[v]))
        };
    }
    for _ in 0..sc.read::<usize>() {
        writeln!(out, "{}", dp[sc.read::<usize>() - 1]).ok();
    }
}
