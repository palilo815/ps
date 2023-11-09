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
    let a = sc.read_vec::<i32>(n);
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
    let mut ans = a[0] as i64;
    for (u, kids) in adj.into_iter().enumerate() {
        ans += kids.into_iter().fold(0, |acc, v| acc + 0.max(a[v] - a[u]) as i64);
    }
    writeln!(out, "{ans}").ok();
}
