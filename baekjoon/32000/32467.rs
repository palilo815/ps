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
    let k = sc.read::<u64>();
    let x = sc.read::<usize>();
    let clubs = (0..n).map(|_| (sc.read::<u32>(), sc.read::<u32>())).collect::<Vec<_>>();
    let parametric = |mut lo, mut hi| {
        let mut buf = Vec::with_capacity(n);
        let mut f = |mid| -> bool {
            buf.clear();
            buf.extend(clubs.iter().filter(|x| x.0 > mid).map(|x| (x.0 - mid) as u64 * x.1 as u64));
            if buf.len() < x {
                return true;
            }
            let kill = buf.len() - x + 1;
            buf.select_nth_unstable(kill - 1);
            buf.iter().take(kill).sum::<u64>() < k
        };
        // first true
        while lo != hi {
            let mid = lo + (hi - lo) / 2;
            if f(mid) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        lo
    };
    writeln!(bw, "{}", parametric(0, 1_000_000)).ok();
}
