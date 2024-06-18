use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 200;
    const S: usize = 10;
    let mut a = [0; N + S];
    let mut dp = [0; N + S + 1];
    loop {
        let n = sc.read::<usize>();
        if n == 0 {
            break;
        }
        let s = sc.read::<usize>();
        let t = sc.read::<usize>();
        for x in a.iter_mut().take(n) {
            *x = sc.read::<i32>();
        }
        a[n..n + s].fill(0);
        dp[1..n + s + 1].fill(i32::MIN);
        for _ in 0..t {
            for i in (0..n + 1).rev() {
                if dp[i] == i32::MIN {
                    continue;
                }
                for j in 1..s + 1 {
                    dp[i + j] = dp[i + j].max(dp[i] + a[i + j - 1]);
                }
            }
        }
        writeln!(bw, "{}", dp[n + 1..n + s + 1].iter().max().unwrap()).ok();
    }
}
