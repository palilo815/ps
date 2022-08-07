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

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let l = sc.read::<usize>();
    if l == 0 {
        writeln!(out, "0").ok();
        return;
    }
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut stack = Vec::with_capacity(n);
    let mut dist = vec![0; n];
    let mut dfs = |s: usize| {
        dist.fill(-1);
        dist[s] = 0;
        stack.push(s);
        while let Some(u) = stack.pop() {
            for &v in adj[u].iter() {
                if dist[v] == -1 {
                    dist[v] = dist[u] + 1;
                    stack.push(v);
                }
            }
        }
        dist.iter().enumerate().max_by_key(|x| x.1).unwrap().0
    };
    let root = dfs(0);
    let root = dfs(root);
    let mut topo = vec![0; n];
    stack.push(root);
    for u in topo.iter_mut() {
        *u = stack.pop().unwrap();
        for i in 0..adj[*u].len() {
            let v = adj[*u][i];
            let j = adj[v].iter().position(|x| x == u).unwrap();
            adj[v].swap_remove(j);
            stack.push(v);
        }
    }
    let mut dp = dist;
    dp.fill(0);
    for u in topo.into_iter().rev() {
        if adj[u].is_empty() {
            dp[u] = 1;
        } else {
            let heavy = *adj[u]
                .iter()
                .max_by(|&&lhs, &&rhs| dp[lhs].cmp(&dp[rhs]))
                .unwrap();
            dp[u] = dp[heavy] + 1;
            dp[heavy] = 0;
        }
    }
    let n = n.min((l << 1) - 1);
    dp.select_nth_unstable_by(n - 1, |lhs, rhs| rhs.cmp(lhs));
    writeln!(out, "{}", dp.into_iter().take(n).sum::<i32>()).ok();
}
