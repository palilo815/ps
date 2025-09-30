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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<u64>();
    let m = sc.read::<usize>();
    let a = sc.read_vec::<u64>(m);
    let mut ans = u64::MAX;
    for i in 0..1 << m {
        let mut acc = 0;
        for (j, &x) in a.iter().enumerate() {
            if i >> j & 1 == 1 {
                acc += x;
            }
        }
        if acc >= n {
            ans = ans.min(acc);
        }
    }
    if ans == u64::MAX {
        writeln!(bw, "IMPOSSIBLE").ok();
    } else {
        writeln!(bw, "{ans}").ok();
    }
}
