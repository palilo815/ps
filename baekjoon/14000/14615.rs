#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a String) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

use std::io::Write;

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let mut adj = vec![vec![]; n];
    let mut rev = adj.clone();
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        adj[u].push(v);
        rev[v].push(u);
    }
    let mut stk = Vec::with_capacity(n);
    let mut dfs = |s: usize, adj: &Vec<Vec<usize>>| {
        let mut visited = vec![false; n];
        visited[s] = true;
        stk.push(s);
        while let Some(u) = stk.pop() {
            for &v in adj[u].iter() {
                if !visited[v] {
                    visited[v] = true;
                    stk.push(v);
                }
            }
        }
        visited
    };
    let d1 = dfs(0, &adj);
    let d2 = dfs(n - 1, &rev);
    let m = sc.next::<usize>();
    for _ in 0..m {
        let x = sc.next::<usize>() - 1;
        writeln!(
            out,
            "{} the CTP",
            if d1[x] && d2[x] {
                "Defend"
            } else {
                "Destroyed"
            }
        )
        .ok();
    }
}
