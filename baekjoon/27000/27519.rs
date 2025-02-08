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
    const M: usize = 100_001;
    const MOD: i32 = 1_000_000_007;
    let mut sieve = vec![false; M];
    sieve[0] = true;
    sieve[1] = true;
    sieve.iter_mut().skip(4).step_by(2).for_each(|x| *x = true);
    let mut i = 3;
    while i * i < M {
        if !sieve[i] {
            sieve.iter_mut().skip(i * i).step_by(i * 2).for_each(|x| *x = true);
        }
        i += 2;
    }
    let mut dp = vec![0; M];
    dp[0] = 1;
    for (i, b) in sieve.into_iter().enumerate() {
        if b {
            continue;
        }
        for j in i..M {
            dp[j] += dp[j - i];
            if dp[j] >= MOD {
                dp[j] -= MOD;
            }
        }
    }
    let t = sc.read::<usize>();
    for _ in 0..t {
        writeln!(bw, "{}", dp[sc.read::<usize>()]).ok();
    }
}
