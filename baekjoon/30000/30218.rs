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
    let k = sc.read::<usize>();
    let a = sc.read_vec::<usize>(n);
    let mut sum = a.iter().take(k).sum::<usize>();
    let mut res = a.iter().enumerate().take(k).fold(0, |acc, (i, x)| acc + (i + 1) * x);
    let mut ans = vec![(0, 0); n - k + 1];
    ans[0] = (res, 1);
    for i in 0..n - k {
        res -= a[i];
        sum -= a[i];
        res += k * a[i + k] - sum;
        sum += a[i + k];
        ans[i + 1] = (res, i + 2);
    }
    ans.sort_unstable();
    for (x, i) in ans {
        writeln!(out, "{i} {x}").ok();
    }
}
