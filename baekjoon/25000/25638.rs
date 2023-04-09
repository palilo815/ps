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
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let a = sc.read_vec::<u8>(n);
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
    let mut sub = vec![[0u32; 2]; n];
    for &u in topo.iter().rev() {
        sub[u] = adj[u]
            .iter()
            .fold([0, 0], |acc, &v| [acc[0] + sub[v][0], acc[1] + sub[v][1]]);
        sub[u][a[u] as usize] += 1;
    }
    let dp = (0..n)
        .map(|u| {
            let mut acc = 0;
            let mut prv = [sub[0][0] - sub[u][0], sub[0][1] - sub[u][1]];
            for &v in adj[u].iter() {
                acc += prv[0] * sub[v][1] + prv[1] * sub[v][0];
                prv[0] += sub[v][0];
                prv[1] += sub[v][1];
            }
            acc
        })
        .collect::<Vec<_>>();
    let q = sc.read::<usize>();
    for _ in 0..q {
        writeln!(out, "{}", dp[sc.read::<usize>() - 1]).ok();
    }
}
