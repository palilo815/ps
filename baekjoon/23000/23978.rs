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
    let n = sc.read::<usize>();
    let k = sc.read::<i64>();
    let a = sc.read_vec::<i32>(n);
    let parametric = |mut lo, mut hi| {
        let f = |mid: i64| -> bool {
            let earn = a.windows(2).fold((mid + 1) * mid / 2, |acc, w| {
                let interval = mid.min((w[1] - w[0]) as i64);
                acc + (mid + mid + 1 - interval) * interval / 2
            });
            earn >= k
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
    let ans = parametric(1, 1414213562);
    writeln!(bw, "{ans}").ok();
}
