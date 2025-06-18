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
    let cmp_by_slope = |a: &(u64, u64), b: &(u64, u64)| (a.1 * b.0).cmp(&(a.0 * b.1));
    let n = sc.read::<usize>();
    let layer = (0..n)
        .map(|_| {
            (
                (sc.read::<u64>(), sc.read::<u64>()),
                (sc.read::<u64>(), sc.read::<u64>()),
            )
        })
        .collect::<Vec<_>>();
    let m = sc.read::<usize>();
    let mut laser = (0..m).map(|_| (sc.read::<u64>(), sc.read::<u64>())).collect::<Vec<_>>();
    laser.sort_unstable_by(cmp_by_slope);
    let mut ans = n;
    for (mut u, mut v) in layer {
        if cmp_by_slope(&u, &v) == std::cmp::Ordering::Greater {
            std::mem::swap(&mut u, &mut v);
        }
        let i = laser.partition_point(|p| cmp_by_slope(p, &u) == std::cmp::Ordering::Less);
        if i != m && cmp_by_slope(&laser[i], &v) != std::cmp::Ordering::Greater {
            ans -= 1;
        }
    }
    writeln!(bw, "{ans}").ok();
}
