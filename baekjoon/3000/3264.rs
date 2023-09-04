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
    let s = sc.read::<usize>() - 1;
    let mut adj = vec![vec![]; n];
    let mut ans = 0;
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        let w = sc.read::<u32>();
        adj[u].push((w, v));
        adj[v].push((w, u));
        ans += w;
    }
    ans <<= 1;
    let mut dist = vec![u32::MAX; n];
    dist[s] = 0;
    let mut stack = Vec::with_capacity(n);
    stack.push(s);
    while let Some(u) = stack.pop() {
        for &(w, v) in adj[u].iter() {
            if dist[v] == u32::MAX {
                dist[v] = dist[u] + w;
                stack.push(v);
            }
        }
    }
    ans -= dist.into_iter().max().unwrap();
    writeln!(out, "{ans}").ok();
}
