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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    if n == 1 {
        writeln!(bw, "0").ok();
        return;
    }
    let h = sc.read_vec::<i32>(n);
    let mut dp_odd = vec![0; n];
    let mut dp_even = h.windows(2).map(|w| w[0].abs_diff(w[1])).collect::<Vec<_>>();
    write!(bw, "0 {}", dp_even.iter().min().unwrap()).ok();
    for i in 2..n {
        let dp = if i & 1 == 0 { &mut dp_odd } else { &mut dp_even };
        for j in 0..dp.len() - 2 {
            dp[j] = dp[j + 1] + h[j].abs_diff(h[j + i]);
        }
        dp.pop();
        dp.pop();
        write!(bw, " {}", dp.iter().min().unwrap()).ok();
    }
}
