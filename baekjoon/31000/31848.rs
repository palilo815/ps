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
    let n = sc.read::<i32>();
    let mut a = (0..n).map(|i| (i, (sc.read::<i32>() + i))).collect::<Vec<_>>();
    a.dedup_by(|cur, prv| cur.1 <= prv.1);
    let q = sc.read::<i32>();
    for _ in 0..q {
        let s = sc.read::<i32>();
        let ans = a.partition_point(|x| x.1 < s);
        write!(bw, "{} ", a[ans].0 + 1).ok();
    }
}
