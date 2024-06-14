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
    let mut s = sc.read::<i32>();
    let mut v = Vec::with_capacity(n * 2);
    for _ in 0..n {
        let a = sc.read::<i32>();
        let k = sc.read::<i32>();
        v.push((k, a / k));
        if a % k != 0 {
            v.push((a % k, 1));
        }
    }
    v.sort_unstable_by(|l, r| r.0.cmp(&l.0));
    let mut ans = 0;
    for (coef, def) in v {
        let army = def.min(s);
        s -= army;
        ans += (def - army) as i64 * coef as i64;
    }
    writeln!(bw, "{ans}").ok();
}
