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
    const N: usize = 10_000;
    const INF: i32 = 0x3f3f3f3f;
    let do_or = |l: [i32; 2], r: [i32; 2]| -> [i32; 2] {
        [INF.min(l[0] + r[0]), (INF.min(l[1] + r[1])).min((l[0] + r[1]).min(l[1] + r[0]))]
    };
    let do_and = |l: [i32; 2], r: [i32; 2]| -> [i32; 2] {
        [(INF.min(l[0] + r[0])).min((l[0] + r[1]).min(l[1] + r[0])), INF.min(l[1] + r[1])]
    };
    let mut gate = [[0, 0]; N / 2];
    let mut dp = [[0, 0]; N];
    let t = sc.read::<usize>();
    for t in 1..=t {
        let n = sc.read::<usize>();
        let v = sc.read::<usize>();
        let gate = &mut gate[..n / 2];
        let dp = &mut dp[..n];
        for x in gate.iter_mut() {
            x[0] = sc.read::<u32>();
            x[1] = sc.read::<u32>();
        }
        for x in dp.iter_mut().skip(n / 2) {
            *x = [INF, INF];
            x[sc.read::<usize>()] = 0;
        }
        for (i, g) in gate.iter().enumerate().rev() {
            dp[i] = if g[0] == 0 {
                do_or(dp[i * 2 + 1], dp[i * 2 + 2])
            } else {
                do_and(dp[i * 2 + 1], dp[i * 2 + 2])
            };
            if g[1] == 1 {
                let tp = if g[0] == 0 {
                    do_and(dp[i * 2 + 1], dp[i * 2 + 2])
                } else {
                    do_or(dp[i * 2 + 1], dp[i * 2 + 2])
                };
                dp[i][0] = dp[i][0].min(tp[0] + 1);
                dp[i][1] = dp[i][1].min(tp[1] + 1);
            }
        }
        if dp[0][v] == INF {
            writeln!(out, "Case #{t}: IMPOSSIBLE").ok();
        } else {
            writeln!(out, "Case #{t}: {}", dp[0][v]).ok();
        }
    }
}
