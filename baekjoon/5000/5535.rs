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
    let d = sc.read::<usize>();
    let n = sc.read::<usize>();
    let t = sc.read_vec::<i32>(d);
    let clothes = (0..n)
        .map(|_| (sc.read::<i32>(), sc.read::<i32>(), sc.read::<usize>()))
        .collect::<Vec<_>>();
    const NEG: i32 = !0x3f3f3f3f;
    let mut dp = [NEG; 101];
    for &(_, _, c) in clothes
        .iter()
        .filter(|cloth| cloth.0 <= t[0] && t[0] <= cloth.1)
    {
        dp[c] = 0;
    }
    for t in t.into_iter().skip(1) {
        let tp = dp;
        dp.fill(NEG);
        for &(_, _, c) in clothes.iter().filter(|cloth| cloth.0 <= t && t <= cloth.1) {
            for (i, t) in tp.into_iter().enumerate() {
                dp[c] = dp[c].max(t + c.abs_diff(i) as i32);
            }
        }
    }
    writeln!(out, "{}", dp.iter().max().unwrap()).ok();
}
