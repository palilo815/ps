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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
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
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let v = sc.read_vec::<i32>(n);
        let mut adj = vec![vec![]; n];
        let mut topo = Vec::with_capacity(n);
        for i in 0..n {
            let p = sc.read::<usize>();
            if p == 0 {
                topo.push(i);
            } else {
                adj[p - 1].push(i);
            }
        }
        let root = topo[0];
        for i in 0..n {
            let u = topo[i];
            for &v in adj[u].iter() {
                topo.push(v);
            }
        }
        let mut dp = vec![(0, 0); n]; // (in, not-in)
        for u in topo.into_iter().rev() {
            dp[u].0 = adj[u].iter().fold(v[u] as i64, |acc, &v| acc + dp[v].1);
            if adj[u].is_empty() {
                continue;
            }
            if adj[u].iter().all(|&v| dp[v].0 < dp[v].1) {
                let best_index = adj[u]
                    .iter()
                    .enumerate()
                    .max_by_key(|(_, &v)| dp[v].0 - dp[v].1)
                    .unwrap()
                    .0;
                dp[u].1 += dp[adj[u][best_index]].0;
                adj[u].swap_remove(best_index);
            }
            dp[u].1 += adj[u].iter().fold(0, |acc, &v| acc + dp[v].0.max(dp[v].1));
        }
        writeln!(out, "{}", dp[root].0.max(dp[root].1)).ok();
    }
}
