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

pub trait ChangeMinMax {
    fn chmin(&mut self, x: Self) -> bool;
    fn chmax(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChangeMinMax for T {
    fn chmin(&mut self, x: Self) -> bool {
        *self > x && {
            *self = x;
            true
        }
    }
    fn chmax(&mut self, x: Self) -> bool {
        *self < x && {
            *self = x;
            true
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
    let n: usize = sc.next();
    let m: usize = sc.next();
    let k: usize = sc.next();
    let mut a = sc.next_vec::<i32>(n);
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<i32>();
        adj[u].push((w, v));
        adj[v].push((w, u));
    }
    let prv = {
        const INF: i32 = 0x3f3f3f3f;
        let mut par = vec![-1; n];
        let mut dist = vec![INF; n];
        dist[0] = 0;
        let mut pq = std::collections::BinaryHeap::new();
        pq.push(std::cmp::Reverse((0, 0)));
        while let Some(std::cmp::Reverse((d, u))) = pq.pop() {
            if d != dist[u] {
                continue;
            }
            for &(c, v) in adj[u].iter() {
                let d = d + c;
                if dist[v] > d {
                    dist[v] = d;
                    par[v] = u as i32;
                    pq.push(std::cmp::Reverse((d, v)));
                } else if dist[v] == d {
                    par[v].chmax(u as i32);
                }
            }
        }
        par
    };
    let mut par = vec![-1; n];
    for u in 0..n {
        if a[u] == 0 {
            par[u] = prv[u]
        }
    }
    for _ in 0..k {
        let mut u = sc.next::<usize>() - 1;
        while par[u] != -1 {
            let p = par[u] as usize;
            if par[p] != -1 {
                par[u] = par[p];
            }
            u = p;
        }
        let ans = {
            if (u != 0 && prv[u] == -1) || a[u] == 0 {
                -1
            } else {
                a[u] -= 1;
                if a[u] == 0 {
                    par[u] = prv[u];
                }
                u as i32 + 1
            }
        };
        writeln!(out, "{}", ans).ok();
    }
}
