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
    let m = sc.read::<usize>();
    let mut pref = vec![0; n + 1];
    for i in 0..n {
        pref[i + 1] = pref[i] + sc.read::<u64>();
    }
    let mut p = [0; 7];
    for x in p.iter_mut().take(m) {
        *x = sc.read::<u64>();
    }
    let perms = {
        let mut res = Vec::with_capacity(7 * 6 * 5 * 4 * 3 * 2);
        let mut c = [0; 7];
        let mut i = 0;
        res.push(p);
        while i < m {
            if c[i] < i {
                p.swap(i, if i % 2 == 0 { 0 } else { c[i] });
                res.push(p);
                c[i] += 1;
                i = 0;
            } else {
                c[i] = 0;
                i += 1;
            }
        }
        res
    };
    let parametric = |mut lo, mut hi| {
        let f = |mid| -> bool {
            for p in perms.iter() {
                let mut i = 0;
                for &man in p.iter() {
                    i = pref.partition_point(|&x| x <= pref[i] + man * mid) - 1;
                }
                if i == n {
                    return true;
                }
            }
            false
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
    writeln!(bw, "{}", parametric(1, pref[n])).ok();
}
