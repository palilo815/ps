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

#[derive(Clone, Copy)]
struct Pack {
    advertised: usize,
    real: usize,
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const M: usize = 2000;
    let b = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut dp = [0; M];
    let mut packs = vec![Pack { advertised: 1, real: 1 }];
    let mut ans = usize::MAX;
    for _ in 0..k {
        dp[1..].fill(usize::MAX);
        for &Pack { advertised, real } in packs.iter() {
            for i in advertised..M {
                if dp[i - advertised] != usize::MAX {
                    dp[i] = dp[i].min(dp[i - advertised] + real);
                }
            }
        }
        let l = sc.read::<usize>();
        packs = (0..l)
            .map(|_| {
                let advertised = sc.read::<usize>();
                Pack {
                    advertised,
                    real: *dp[advertised..].iter().find(|&&real| real != usize::MAX).unwrap(),
                }
            })
            .collect::<Vec<_>>();
        if let Some(res) = packs.iter().find(|p| p.real >= b) {
            ans = ans.min(res.advertised);
        }
    }
    if ans != usize::MAX {
        writeln!(bw, "{ans}").ok();
    } else {
        writeln!(bw, "impossible").ok();
    }
}
