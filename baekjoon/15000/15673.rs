use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
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
    let a = sc.read_vec::<i32>(n);
    let mut pref = vec![(0, 0); n + 1];
    for i in 0..n {
        pref[i + 1] = (a[i] + 0.min(pref[i].0), a[i] + 0.max(pref[i].1));
    }
    for i in 1..n {
        pref[i + 1].0 = pref[i + 1].0.min(pref[i].0);
        pref[i + 1].1 = pref[i + 1].1.max(pref[i].1);
    }
    let mut ans = i64::MIN;
    let mut suff = (0, 0);
    for i in (1..n).rev() {
        suff = (a[i] + 0.min(suff.0), a[i] + 0.max(suff.1));
        let best = std::cmp::max(pref[i].0 as i64 * suff.0 as i64, pref[i].1 as i64 * suff.1 as i64);
        ans = ans.max(best);
    }
    writeln!(out, "{ans}").ok();
}
