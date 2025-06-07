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
    const N: usize = 1_000_000;
    let mut a = vec![(0, 0); N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        a.fill_with(|| (sc.read::<i32>(), sc.read::<i32>() + 1));
        a.sort_by(|l, r| l.0.cmp(&r.0));
        let mut ans = 0;
        let mut lmost = i32::MIN;
        let mut rmost = i32::MIN;
        for &(l, r) in a.iter() {
            if rmost < l {
                ans += rmost - lmost;
                lmost = l;
            }
            rmost = rmost.max(r);
        }
        ans += rmost - lmost;
        writeln!(bw, "{ans}").ok();
    }
}
