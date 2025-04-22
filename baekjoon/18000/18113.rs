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
    let k = sc.read::<u32>();
    let m = sc.read::<u64>();
    let a = (0..n)
        .map(|_| {
            let l = sc.read::<u32>();
            if l >= 2 * k {
                l - 2 * k
            } else {
                l.saturating_sub(k)
            }
        })
        .collect::<Vec<_>>();
    if a.iter().fold(0, |acc, &x| acc + x as u64) < m {
        writeln!(bw, "-1").ok();
        return;
    }
    let parametric = |mut lo, mut hi| {
        let f = |mid| -> bool { a.iter().fold(0, |acc, &x| acc + (x / mid) as u64) >= m };
        // last true
        while lo != hi {
            let mid = hi - (hi - lo) / 2;
            if f(mid) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        lo
    };
    writeln!(bw, "{}", parametric(1, *a.iter().max().unwrap())).ok();
}

