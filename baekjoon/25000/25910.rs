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
    let x = sc.read::<u32>();
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        let w = sc.read::<u32>();
        adj[u].push((w, v));
        adj[v].push((w, u));
    }
    let mut topo = vec![0; n];
    let mut j = 1;
    for i in 0..n {
        let u = topo[i];
        for (_, v) in adj[u].clone() {
            let p = adj[v].iter().position(|e| e.1 == u).unwrap();
            adj[v].swap_remove(p);
            topo[j] = v;
            j += 1;
        }
    }
    let mut dp = vec![0; n];
    let mut sum = vec![0; n];
    let mut solve = |p: u32| {
        dp.fill(0);
        dp[0] = x >> p & 1;
        for &u in topo.iter() {
            for &(w, v) in adj[u].iter() {
                dp[v] = dp[u] ^ (w >> p & 1);
            }
        }
        dp[0] = dp.iter().sum();
        for &u in topo.iter() {
            for &(w, v) in adj[u].iter() {
                dp[v] = if (w >> p & 1) == 1 {
                    n as u32 - dp[u]
                } else {
                    dp[u]
                };
            }
        }
        for (sum, dp) in sum.iter_mut().zip(dp.iter()) {
            *sum += *dp;
        }
    };
    for i in 0..20 {
        solve(i);
    }
    writeln!(out, "{}", sum.into_iter().min().unwrap()).ok();
}
