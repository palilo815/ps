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
    const M: usize = 1 << 20;
    let mut dp = vec![false; M];
    let mut mat = [[0; 20]; 20];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        for i in 0..n {
            for j in 0..n {
                mat[i][j] = sc.read::<i32>();
            }
        }
        let m = 1 << n;
        let dp = &mut dp[..m];
        dp.fill(false);
        dp[m - 1] = true;
        for i in (1..m).rev() {
            if dp[i] {
                for u in 0..n {
                    if i >> u & 1 == 1 {
                        let mut acc = 0;
                        for v in 0..n {
                            if i >> v & 1 == 1 {
                                acc += mat[u][v];
                            }
                        }
                        dp[i ^ (1 << u)] |= acc.is_positive();
                    }
                }
            }
        }
        let mut any = false;
        for i in 0..n {
            if dp[1 << i] {
                any = true;
                write!(out, "{} ", i + 1).ok();
            }
        }
        writeln!(out, "{}", if any { "" } else { "0" }).ok();
    }
}
