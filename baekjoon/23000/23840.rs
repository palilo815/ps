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
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<usize>();
        adj[u].push((w, v));
        adj[v].push((w, u));
    }
    let s = sc.next::<usize>() - 1;
    let t = sc.next::<usize>() - 1;
    let m = sc.next::<usize>();
    let mut a = vec![0; m + 2];
    a[0] = s;
    a[m + 1] = t;
    for i in 1..=m {
        a[i] = sc.next::<usize>() - 1;
    }
    let m = m + 2;
    let mut pq = std::collections::BinaryHeap::new();
    let mut dp = vec![0; n];
    const INF: usize = usize::MAX >> 2;
    let adj = a
        .iter()
        .map(|&s| {
            dp.fill(INF);
            dp[s] = 0;
            pq.push(std::cmp::Reverse((0, s)));
            while let Some(std::cmp::Reverse((d, u))) = pq.pop() {
                if d != dp[u] {
                    continue;
                }
                for &(w, v) in adj[u].iter() {
                    let d = d + w;
                    if dp[v] > d {
                        dp[v] = d;
                        pq.push(std::cmp::Reverse((d, v)));
                    }
                }
            }
            a.iter().map(|&x| dp[x]).collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();
    let mut dp = vec![[INF; 22]; 1 << m];
    dp[1][0] = 0;
    for mask in 0..1 << m {
        for u in 0..m {
            if (mask >> u & 1) == 0 || dp[mask][u] == INF {
                continue;
            }
            let cur = dp[mask][u];
            for v in 0..m {
                if (mask >> v & 1) == 1 {
                    continue;
                }
                dp[mask | 1 << v][v].chmin(cur + adj[u][v]);
            }
        }
    }
    let ans = dp[(1 << m) - 1][m - 1];
    writeln!(out, "{}", if ans == INF { -1 } else { ans as isize }).ok();
}
