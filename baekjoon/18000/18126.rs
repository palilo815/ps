use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
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
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<u32>();
        adj[u].push((w, v));
        adj[v].push((w, u));
    }
    let mut dist = vec![u64::MAX; n];
    dist[0] = 0;
    let mut stk = Vec::with_capacity(n);
    stk.push(0);
    while let Some(u) = stk.pop() {
        for &(w, v) in adj[u].iter() {
            if dist[v] == u64::MAX {
                dist[v] = dist[u] + w as u64;
                stk.push(v);
            }
        }
    }
    writeln!(out, "{}", dist.iter().max().unwrap()).ok();
}
