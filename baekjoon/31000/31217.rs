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
    let m = sc.read::<usize>();
    let mut deg = vec![0; n];
    for _ in 0..m {
        deg[sc.read::<usize>() - 1] += 1;
        deg[sc.read::<usize>() - 1] += 1;
    }
    const MOD: i64 = 1_000_000_007;
    let mut ans = 0;
    for d in deg {
        ans += d * (d - 1) * (d - 2) / 6;
        ans %= MOD;
    }
    writeln!(out, "{ans}").ok();
}
