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
    const N: usize = 100;
    let mut cnt = [0; N];
    let mut sum = [0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        let cnt = &mut cnt[..m];
        let sum = &mut sum[..m];
        cnt.fill(0);
        sum.fill(0);
        for i in 0..n {
            for j in 0..m {
                if sc.read::<char>() == '1' {
                    cnt[j] += 1;
                    sum[j] += n - i;
                }
            }
        }
        let ans = cnt.iter().zip(sum.iter()).map(|(c, s)| s - c * (c + 1) / 2).sum::<usize>();
        writeln!(bw, "{ans}").ok();
    }
}
