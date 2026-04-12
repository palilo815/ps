use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = Vec::new();
        stdin().lock().read_to_end(&mut buf).ok();
        let s = unsafe { std::str::from_utf8_unchecked(Box::leak(buf.into_boxed_slice())) };
        Self { it: s.split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut dp = vec![false; n];
    for _ in 0..m {
        dp[sc.read::<usize>()] = true;
    }
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>();
        let v = sc.read::<usize>();
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut stk = Vec::with_capacity(n);
    stk.push(0);
    for i in 0..n {
        let u = stk[i];
        stk.extend_from_slice(&adj[u]);
        for i in 0..adj[u].len() {
            let v = adj[u][i];
            let p = adj[v].iter().position(|&x| x == u).unwrap();
            adj[v].swap_remove(p);
        }
    }
    for &u in stk.iter().rev() {
        dp[u] = adj[u].iter().fold(dp[u], |flag, &v| flag | dp[v]);
    }
    stk.clear();
    stk.push(0);
    let mut ans = Vec::with_capacity(2 * n);
    while let Some(u) = stk.pop() {
        ans.push(u);
        while let Some(v) = adj[u].pop() {
            if dp[v] {
                stk.push(u);
                stk.push(v);
                break;
            }
        }
    }
    writeln!(bw, "{}", ans.len() - 1).ok();
    for x in ans {
        write!(bw, "{x} ").ok();
    }
}
