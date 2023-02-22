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
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let val = (0..n)
        .map(|_| [sc.read::<u32>(), sc.read::<u32>(), sc.read::<u32>()])
        .collect::<Vec<_>>();
    let mut topo = Vec::with_capacity(n);
    topo.push(0);
    for i in 0..n {
        let u = topo[i];
        for v in adj[u].clone() {
            let j = adj[v].iter().position(|&x| x == u).unwrap();
            adj[v].swap_remove(j);
        }
        topo.extend_from_slice(&adj[u]);
    }
    let mut dp = vec![[0; 3]; n];
    for &u in topo.iter().rev() {
        dp[u] = adj[u].iter().fold(val[u], |acc, &v| {
            [
                acc[0] + dp[v][1].max(dp[v][2]),
                acc[1] + dp[v][2].max(dp[v][0]),
                acc[2] + dp[v][0].max(dp[v][1]),
            ]
        });
    }
    const RGB: [u8; 3] = [b'R', b'G', b'B'];
    let mut trace = vec![0; n];
    for u in topo.into_iter() {
        let i = dp[u]
            .iter()
            .enumerate()
            .max_by(|l, r| l.1.cmp(r.1))
            .unwrap()
            .0;
        trace[u] = RGB[i];
        for &v in adj[u].iter() {
            dp[v][i] = 0;
        }
    }
    writeln!(out, "{}", dp[0].iter().max().unwrap()).ok();
    writeln!(out, "{}", String::from_utf8(trace).unwrap()).ok();
}
