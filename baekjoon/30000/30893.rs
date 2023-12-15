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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let s = sc.read::<usize>() - 1;
    let e = sc.read::<usize>() - 1;
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut par = vec![usize::MAX; n];
    par[s] = usize::MAX - 1;
    let mut stack = Vec::with_capacity(n);
    stack.push(s);
    for i in 0..n {
        let u = stack[i];
        for &v in adj[u].iter() {
            if par[v] == usize::MAX {
                par[v] = u;
                stack.push(v);
            }
        }
    }
    stack.clear();
    let mut u = e;
    while u != s {
        u = par[u];
        stack.push(u);
    }
    let first = stack.into_iter().rev().skip(1).step_by(2).all(|u| adj[u].len() == 2);
    writeln!(out, "{}", if first { "First" } else { "Second" }).ok();
}
