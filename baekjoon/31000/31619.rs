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
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let q = sc.read::<usize>();
    let goods = (0..n).map(|_| (sc.read::<i64>(), sc.read::<usize>() - 1)).collect::<Vec<_>>();
    let mut pref1 = vec![0; n + 1];
    for i in 0..n {
        pref1[i + 1] = pref1[i] + goods[i].0;
    }
    let mut count = vec![0; m + 1];
    for &(_, a) in goods.iter() {
        count[a + 1] += 1;
    }
    for i in 0..m {
        count[i + 1] += count[i];
    }
    let mut sorted = vec![(0, 0, 0); n];
    for (i, (p, a)) in goods.into_iter().enumerate() {
        sorted[count[a]] = (p, a, i);
        count[a] += 1;
    }
    let mut pref2 = vec![0; n + 1];
    for i in 0..n {
        pref2[i + 1] = pref2[i] + sorted[i].0;
    }
    for _ in 0..q {
        let t = sc.read::<usize>() - 1;
        let l = sc.read::<usize>() - 1;
        let r = sc.read::<usize>();
        let price = pref1[r] - pref1[l];
        let lb = sorted.partition_point(|x| x.1 < t || x.1 == t && x.2 < l);
        let ub = sorted.partition_point(|x| x.1 < t || x.1 == t && x.2 < r);
        let discount = (pref2[ub] - pref2[lb]) / 2;
        writeln!(bw, "{}", price - discount).ok();
    }
}
