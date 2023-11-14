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
    let t = sc.read_vec::<i32>(n);
    let b = sc.read_vec::<i32>(n);
    let c = sc.read_vec::<i32>(n);
    let mut dp = vec![0; n + 1];
    for i in 0..n {
        let j = t.partition_point(|&v| v < t[i] - b[i]);
        dp[i + 1] = dp[i].max(dp[j] + c[i] as i64);
    }
    writeln!(out, "{}", dp[n]).ok();
}
