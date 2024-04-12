use std::io::*;

struct Scanner {
    it: std::str::SplitWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut out = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let s = sc.read::<i32>();
    let e = sc.read::<i32>();
    let segs = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    let mut ls = segs.iter().filter(|x| x.0 <= s).map(|x| x.1).collect::<Vec<_>>();
    let mut rs = segs.iter().filter(|x| x.1 >= e).map(|x| x.0).collect::<Vec<_>>();
    ls.sort_unstable();
    rs.sort_unstable_by(|l, r| r.cmp(l));
    let mut best = i32::MAX;
    for (l, r) in segs.into_iter() {
        if l <= s && e <= r {
            writeln!(out, "0").ok();
            return;
        }
        let mut sum = 0;
        if s < l {
            let i = ls.partition_point(|&x| x < l);
            if i == ls.len() {
                continue;
            }
            sum += ls[i] - l;
        }
        if r < e {
            let i = rs.partition_point(|&x| x > r);
            if i == rs.len() {
                continue;
            }
            sum += r - rs[i];
        }
        best = best.min(sum);
    }
    writeln!(out, "{}", if best == i32::MAX { -1 } else { best }).ok();
}
