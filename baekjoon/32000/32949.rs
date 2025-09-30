use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let t = sc.read::<usize>();
    let mut routines = vec![vec![]; 101];
    for _ in 0..n {
        let s = sc.read::<usize>();
        let p = sc.read::<usize>();
        let h = sc.read::<i64>();
        routines[s].push((p, h));
    }
    let mut dp = vec![-1; t + 1];
    dp[0] = 0;
    let mut tp = vec![0; t + 1];
    let ans = routines
        .into_iter()
        .map(|r| {
            tp.fill(-1);
            for (p, h) in r {
                for x in (p..=t).rev() {
                    if dp[x - p] != -1 {
                        tp[x] = tp[x].max(dp[x - p] + h);
                    }
                    if tp[x - p] != -1 {
                        tp[x] = tp[x].max(tp[x - p] + h);
                    }
                }
            }
            std::mem::swap(&mut dp, &mut tp);
            *dp.iter().max().unwrap()
        })
        .max()
        .unwrap();
    writeln!(bw, "{}", ans.max(0)).ok();
}
