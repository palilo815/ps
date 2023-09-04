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

#[derive(Eq, PartialEq, Clone, Copy)]
struct HeapNode(u32, usize);

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
    let n = sc.read::<usize>();
    let p = (0..n)
        .map(|i| if i == 0 { usize::MAX } else { sc.read::<usize>() - 1 })
        .collect::<Vec<_>>();
    let b = sc.read_vec::<u32>(n);
    let a = sc.read_vec::<u32>(n);
    let mut dp = vec![std::collections::BinaryHeap::new(); n];
    for u in (0..n).rev() {
        dp[u].push(HeapNode(a[u], u));
        let limit = b[u] as usize;
        while dp[u].len() > limit {
            dp[u].pop();
        }
        if u != 0 {
            if dp[u].len() > dp[p[u]].len() {
                dp.swap(u, p[u]);
            }
            let tmp = std::mem::take(&mut dp[u]);
            dp[p[u]].extend(tmp);
        }
    }
    let mut ans = dp[0].clone().into_vec();
    ans.sort_unstable_by(|l, r| l.1.cmp(&r.1));
    writeln!(out, "{}", ans.iter().fold(0, |acc, x| acc + x.0 as u64)).ok();
    write!(out, "{}", ans.len()).ok();
    for x in ans.into_iter() {
        write!(out, " {}", x.1 + 1).ok();
    }
}
