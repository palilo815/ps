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
    let q = sc.read::<usize>();
    let x = sc.read_vec::<i32>(n);
    let y = sc.read_vec::<i32>(n);
    let mut pref = vec![0.0; n];
    let mut suff = vec![0.0; n];
    for i in 1..n {
        let dx = (x[i - 1] - x[i]) as i64;
        let dy = (y[i - 1] - y[i]) as i64;
        let dist = ((dx * dx + dy * dy) as f64).sqrt();
        let w = match y[i].cmp(&y[i - 1]) {
            std::cmp::Ordering::Less => 1.0,
            std::cmp::Ordering::Equal => 2.0,
            std::cmp::Ordering::Greater => 3.0,
        };
        pref[i] = pref[i - 1] + dist * w;
        suff[i] = suff[i - 1] + dist * (4.0 - w);
    }
    for _ in 0..q {
        let i = sc.read::<usize>() - 1;
        let j = sc.read::<usize>() - 1;
        let ans = if i < j { pref[j] - pref[i] } else { suff[i] - suff[j] };
        writeln!(bw, "{ans:.5}").ok();
    }
}
