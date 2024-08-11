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
    let k = sc.read::<usize>();
    let mut cnt = vec![0; k];
    let mut a = (0..n).map(|i| (sc.read::<usize>() - 1, i + 1)).collect::<Vec<_>>();
    a.iter().for_each(|x| cnt[x.0] += 1);
    if *cnt.iter().max().unwrap() > n / 2 {
        writeln!(bw, "-1").ok();
        return;
    }
    for _ in 0..n / 2 {
        let mx = cnt.iter().enumerate().max_by_key(|x| x.1).unwrap().0;
        let i = (0..).find(|&i| (a[i].0 == mx || a[i + 1].0 == mx) && a[i].0 != a[i + 1].0).unwrap();
        writeln!(bw, "{} {}", a[i].1, a[i + 1].1).ok();
        cnt[a[i].0] -= 1;
        cnt[a[i + 1].0] -= 1;
        a.remove(i + 1);
        a.remove(i);
    }
}
