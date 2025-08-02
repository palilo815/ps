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
    let mut a = sc.read_vec::<i32>(n);
    if *a.iter().max().unwrap() > k {
        writeln!(bw, "0").ok();
        return;
    }
    let mn = *a.iter().min().unwrap();
    if mn <= 0 {
        writeln!(bw, "-1").ok();
        return;
    }
    *a.iter_mut().find(|x| **x == mn).unwrap() = k;
    let ans = a.into_iter().fold(1, |acc, x| acc + ((k - x) / mn) as i64);
    writeln!(bw, "{ans}").ok();
}
