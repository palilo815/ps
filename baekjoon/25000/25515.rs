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
    let mut par = vec![usize::MAX; n];
    let mut deg = vec![0; n];
    for _ in 1..n {
        let p = sc.read::<usize>();
        let u = sc.read::<usize>();
        par[u] = p;
        deg[p] += 1;
    }
    let mut dp = sc.read_vec::<i64>(n);
    let mut rev_topo = (0..n).filter(|&i| deg[i] == 0).collect::<Vec<_>>();
    for i in 0..n - 1 {
        let u = rev_topo[i];
        let p = par[u];
        dp[p] += 0.max(dp[u]);
        deg[p] -= 1;
        if deg[p] == 0 {
            rev_topo.push(p);
        }
    }
    writeln!(out, "{}", dp[0]).ok();
}
