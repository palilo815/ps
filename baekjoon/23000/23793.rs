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
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<i32>();
        adj[u].push((w, v));
    }
    let s = sc.next::<usize>() - 1;
    let m = sc.next::<usize>() - 1;
    let t = sc.next::<usize>() - 1;
    let mut dist = vec![i32::MAX; n << 1];
    dist[s] = 0;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(std::cmp::Reverse((0, s)));
    while let Some(std::cmp::Reverse((d, u))) = pq.pop() {
        if d != dist[u] {
            continue;
        }
        let mask = if u >= n { n } else { 0 };
        let u = if u < n { u } else { u - n };
        for &(w, v) in adj[u].iter() {
            let mask = mask | if v == m { n } else { 0 };
            let d = d + w;
            if dist[v + mask] > d {
                dist[v + mask] = d;
                pq.push(std::cmp::Reverse((d, v + mask)));
            }
        }
    }
    if dist[t] == i32::MAX {
        dist[t] = -1;
    }
    if dist[t + n] == i32::MAX {
        dist[t + n] = -1;
    }
    writeln!(out, "{} {}", dist[t + n], dist[t]).ok();
}
