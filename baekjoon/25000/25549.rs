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
    let mut outdeg = vec![0; n];
    let p = (0..n)
        .map(|_| {
            let p = sc.read::<isize>();
            if p == -1 {
                usize::MAX
            } else {
                let p = p as usize - 1;
                outdeg[p] += 1;
                p
            }
        })
        .collect::<Vec<_>>();
    let a = sc.read_vec::<u32>(n);
    let root = p.iter().position(|&x| x == usize::MAX).unwrap();
    let mut rtopo = Vec::with_capacity(n);
    rtopo.extend((0..n).filter(|&i| outdeg[i] == 0));
    for i in 0..n - 1 {
        let p = p[rtopo[i]];
        outdeg[p] -= 1;
        if outdeg[p] == 0 {
            rtopo.push(p);
        }
    }
    let mut dp = vec![std::collections::BinaryHeap::new(); n];
    let mut ans = vec![0; n];
    for u in rtopo.into_iter() {
        dp[u].push(std::cmp::Reverse(a[u]));
        while dp[u].peek().unwrap_or(&std::cmp::Reverse(u32::MAX)).0 <= ans[u] {
            if dp[u].pop().unwrap().0 == ans[u] {
                ans[u] += 1;
            }
        }
        if u != root {
            ans[p[u]] = ans[p[u]].max(ans[u]);
            if dp[u].len() > dp[p[u]].len() {
                dp.swap(u, p[u]);
            }
            let tmp = std::mem::take(&mut dp[u]);
            dp[p[u]].extend(tmp);
        }
    }
    for x in ans.into_iter() {
        writeln!(out, "{x}").ok();
    }
}
