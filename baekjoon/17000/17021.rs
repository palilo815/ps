use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}
fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let k = sc.next::<usize>();
    let a = (0..n)
        .map(|_| (sc.next::<u32>(), sc.next::<u32>() - 1))
        .collect::<Vec<_>>();
    let mut cnt = [0; 26];
    for _ in 0..m {
        cnt[sc.next::<char>() as usize - 'A' as usize] += 1;
    }
    const MOD: u32 = 1_000_000_007;
    let mut dp = vec![0; k];
    dp[0] = 1;
    for i in 1..k {
        for word in a.iter() {
            let len = word.0 as usize;
            if i < len {
                continue;
            }
            dp[i] += dp[i - len];
            if dp[i] >= MOD {
                dp[i] -= MOD;
            }
        }
    }
    let mut dp_end = vec![0; n];
    for (len, rhyme) in a {
        dp_end[rhyme as usize] += dp[k - len as usize];
        if dp_end[rhyme as usize] >= MOD {
            dp_end[rhyme as usize] -= MOD;
        }
    }
    let exp = |mut x: u32, mut p: u32| -> u32 {
        let mut r = 1;
        while p != 0 {
            if p & 1 == 1 {
                r = (r as u64 * x as u64 % MOD as u64) as u32;
            }
            x = (x as u64 * x as u64 % MOD as u64) as u32;
            p >>= 1;
        }
        r
    };
    let ans = cnt.iter().filter(|&&p| p != 0).fold(1, |acc, &p| {
        acc * dp_end.iter().fold(0, |mut acc, &x| {
            acc += exp(x, p);
            if acc >= MOD {
                acc -= MOD;
            }
            acc
        }) as u64
            % MOD as u64
    });
    writeln!(out, "{}", ans).ok();
}
