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
    let n = sc.read::<usize>();
    let m = sc.read::<i32>();
    let mut dp0 = vec![0; n];
    let mut dp1 = vec![0; n];
    let mut who = vec![-1; n];
    for i in 0..m {
        let l = sc.read::<usize>();
        for _ in 0..l {
            let p = sc.read::<usize>() - 1;
            let v = sc.read::<u64>();
            if who[p] == i - 1 {
                let tmp = dp1[p] + v;
                dp1[p] = dp0[p];
                dp0[p] = dp0[p].max(tmp);
            } else {
                dp1[p] = dp0[p];
                dp0[p] += v;
            }
            who[p] = i;
        }
    }
    writeln!(bw, "{}", dp0.into_iter().sum::<u64>()).ok();
}
