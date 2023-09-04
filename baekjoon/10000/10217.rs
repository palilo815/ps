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

#[derive(Eq, PartialEq)]
struct HeapNode(u32, u32, usize);

impl std::cmp::Ord for HeapNode {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0.cmp(&(self.0))
    }
}

impl std::cmp::PartialOrd for HeapNode {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let _ = sc.read::<usize>();
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 0..k {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        let c = sc.read::<u32>();
        let d = sc.read::<u32>();
        adj[u].push((d, c, v));
    }
    const INF: u32 = 0x3f3f3f3f;
    let mut dp = vec![[INF; 100]; m + 1];
    dp[0][0] = 0;
    for c in 0..m {
        for u in 0..n {
            if dp[c][u] == INF {
                continue;
            }
            for &(wd, wc, v) in adj[u].iter() {
                let d = dp[c][u] + wd;
                let c = c + wc as usize;
                if c <= m && d < dp[c][v] {
                    dp[c][v] = d;
                }
            }
        }
    }
    let ans = dp.into_iter().fold(INF, |best, x| best.min(x[n - 1]));
    if ans == INF {
        writeln!(out, "Poor KCM").ok();
    } else {
        writeln!(out, "{ans}").ok();
    }
}
