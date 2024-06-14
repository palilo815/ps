use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let t = sc.read::<usize>();
    const N: usize = 1000;
    let mut a = vec![0; N * N];
    let mut b = vec![0; N * N];
    let mut buf = vec![0; N];
    for _ in 0..t {
        let k = sc.read::<u32>();
        let n = sc.read::<usize>();
        let a = &mut a[..n * n];
        let b = &mut b[..n * n];
        let buf = &mut buf[..n];
        for x in buf.iter_mut() {
            *x = sc.read::<u32>();
        }
        for i in 0..n {
            let x = sc.read::<u32>();
            for j in 0..n {
                a[i * n + j] = x + buf[j];
            }
        }
        for x in buf.iter_mut() {
            *x = sc.read::<u32>();
        }
        for i in 0..n {
            let x = sc.read::<u32>();
            for j in 0..n {
                b[i * n + j] = x + buf[j];
            }
        }
        a.sort_unstable();
        b.sort_unstable();
        let mut ans = u32::MAX;
        let mut i = n * n;
        for x in a.iter() {
            while i != 0 && x + b[i - 1] > k {
                i -= 1;
            }
            if i != 0 && k - x - b[i - 1] <= ans.abs_diff(k) {
                ans = x + b[i - 1];
            }
            if i != n * n && x + b[i] - k < ans.abs_diff(k) {
                ans = x + b[i];
            }
        }
        writeln!(bw, "{ans}").ok();
    }
}
