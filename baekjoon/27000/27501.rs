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
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let val = (0..n)
        .map(|_| (sc.read::<u32>(), sc.read::<u32>(), sc.read::<u32>()))
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
        dp[u][0] = adj[u]
            .iter()
            .fold(val[u].0, |acc, &v| acc + dp[v][1].max(dp[v][2]));
        dp[u][1] = adj[u]
            .iter()
            .fold(val[u].1, |acc, &v| acc + dp[v][2].max(dp[v][0]));
        dp[u][2] = adj[u]
            .iter()
            .fold(val[u].2, |acc, &v| acc + dp[v][0].max(dp[v][1]));
    }
    const RGB: [u8; 3] = [b'R', b'G', b'B'];
    let mut trace = vec![0; n];
    writeln!(out, "{}", dp[0].iter().max().unwrap()).ok();
    for u in topo {
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
    writeln!(out, "{}", String::from_utf8(trace).unwrap()).ok();
}
