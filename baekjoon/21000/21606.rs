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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let s = sc.read_bytes();
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
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
    let mut dp = vec![0; n];
    for u in topo.into_iter().rev() {
        dp[u] = if s[u] == b'0' {
            adj[u].iter().fold(0, |acc, &v| acc + dp[v])
        } else {
            1
        }
    }
    let mut ans = if s[0] == b'0' {
        let m = dp[0] as u64;
        m * (m - 1)
    } else {
        0
    };
    for (u, adj) in adj.into_iter().enumerate() {
        if s[u] == b'1' {
            for v in adj {
                if s[v] == b'0' {
                    let m = (dp[v] + 1) as u64;
                    ans += m * (m - 1);
                } else {
                    ans += 2;
                }
            }
        }
    }
    writeln!(out, "{ans}").ok();
}
