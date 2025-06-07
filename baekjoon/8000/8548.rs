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
    let k = sc.read::<i32>();
    let mut ans = 0;
    let a = sc.read_vec::<i32>(n);
    let mut pref = vec![0; n];
    for i in 1..n {
        pref[i] = pref[i - 1] + 0.max(a[i] - a[i - 1]);
    }
    let mut r = 0;
    for l in 0..n {
        while r != n && pref[r] - pref[l] <= k {
            r += 1;
        }
        ans = ans.max(r - l);
    }
    for i in 1..n {
        pref[i] = pref[i - 1] + 0.max(a[n - i - 1] - a[n - i]);
    }
    let mut r = 0;
    for l in 0..n {
        while r != n && pref[r] - pref[l] <= k {
            r += 1;
        }
        ans = ans.max(r - l);
    }
    writeln!(bw, "{ans}").ok();
}
