use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut a = sc.read_vec::<u64>(n);
    a.sort_unstable();
    let mut events = vec![(0, 0); m << 1];
    for i in 0..m {
        events[i << 1] = (sc.read::<u64>() - 1, 1);
        events[i << 1 | 1] = (sc.read::<u64>(), 0);
    }
    events.sort_unstable();
    let mut ans = (0, 0);
    let mut acc = (0, 0);
    let mut cnt = 0;
    for i in 0..2 * m - 1 {
        if events[i].1 == 1 {
            acc.0 += a[cnt];
            acc.1 += a[n - 1 - cnt];
            cnt += 1;
        } else {
            cnt -= 1;
            acc.0 -= a[cnt];
            acc.1 -= a[n - 1 - cnt];
        }
        let day = events[i + 1].0 - events[i].0;
        ans.0 += acc.0 * day;
        ans.1 += acc.1 * day;
    }
    writeln!(out, "{} {}", ans.0, ans.1).ok();
}
