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

trait ChMinMax {
    fn chmin(&mut self, x: Self) -> bool;
    fn chmax(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChMinMax for T {
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
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let s = sc.read::<usize>();
    let w = sc.read_vec::<usize>(n);
    let t = sc.read_vec::<i32>(n);
    let mut next = vec![usize::MAX; n];
    let has_p = (0..n)
        .map(|i| {
            let p = sc.read::<usize>();
            if p == 0 {
                false
            } else {
                next[p - 1] = i;
                true
            }
        })
        .collect::<Vec<_>>();
    const INF: i32 = 0x3f3f3f3f;
    let mut dp = vec![INF; s + 1];
    dp[0] = 0;
    let mut candi = Vec::with_capacity(n);
    for i in (0..n).filter(|&i| !has_p[i]) {
        candi.clear();
        let mut u = i;
        let mut acc = (0, 0);
        while u != usize::MAX {
            acc.0 += w[u];
            acc.1 += t[u];
            candi.push(acc);
            u = next[u];
        }
        for i in (0..s).rev() {
            if dp[i] == INF {
                continue;
            }
            for &(w, t) in candi.iter() {
                let t2 = dp[i] + t;
                dp[s.min(i + w)].chmin(t2);
            }
        }
    }
    let ans = dp.into_iter().skip(s).min().unwrap();
    writeln!(out, "{}", if ans == INF { -1 } else { ans }).ok();
}
