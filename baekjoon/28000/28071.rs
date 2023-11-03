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
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let a = sc.read_vec::<i32>(n);
    const NEG: i32 = !0x3f3f3f3f;
    let mut dp = vec![NEG; k];
    let mut tp = vec![0; k];
    dp[0] = 0;
    for _ in 0..m {
        tp.copy_from_slice(&dp);
        for (i, &prv) in tp.iter().enumerate() {
            for &x in a.iter() {
                let j = (i + x as usize) % k;
                dp[j] = dp[j].max(prv + x);
            }
        }
    }
    writeln!(out, "{}", dp[0]).ok();
}
