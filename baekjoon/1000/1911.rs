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
    let l = sc.read::<u32>();
    let mut segs = (0..n).map(|_| (sc.read::<u32>(), sc.read::<u32>())).collect::<Vec<_>>();
    segs.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    let mut ans = 0;
    let mut prv = 0;
    for (s, t) in segs {
        prv = prv.max(s);
        if prv < t {
            let need = (t - prv).div_ceil(l);
            ans += need;
            prv += need * l;
        }
    }
    writeln!(bw, "{ans}").ok();
}
