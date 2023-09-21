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
    let p = (0..n).map(|_| sc.read::<usize>() - 1).collect::<Vec<_>>();
    let mut deg = vec![0; n];
    for &p in p.iter() {
        if p != usize::MAX {
            deg[p] += 1;
        }
    }
    let mut rev_topo = (0..n).filter(|&i| deg[i] == 0).collect::<Vec<_>>();
    let mut sz = vec![1; n];
    let mut dp = vec![1; n];
    for i in 0..n - 1 {
        let u = rev_topo[i];
        let p = p[u];
        dp[p] += sz[p] * sz[u] * 2;
        sz[p] += sz[u];
        deg[p] -= 1;
        if deg[p] == 0 {
            rev_topo.push(p);
        }
    }
    let mut ans = (0, 0);
    let mut parity = 0;
    for (i, pairs) in (1usize..).zip(dp.into_iter()) {
        ans.0 += i * (pairs / 2);
        ans.1 += i * (pairs / 2);
        if pairs & 1 == 1 {
            if parity & 1 == 1 {
                ans.0 += i;
            } else {
                ans.1 += i;
            }
        }
        parity ^= pairs;
    }
    writeln!(out, "{} {}", ans.0, ans.1).ok();
}
