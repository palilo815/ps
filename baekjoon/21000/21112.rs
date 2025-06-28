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
    let mut a = (0..n).map(|i| (i, sc.read::<u64>())).collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| l.1.cmp(&r.1));
    let mut ans = 0;
    let mut start = 0;
    let mut max_ord = 0;
    for (i, &(ord, _)) in a.iter().enumerate() {
        max_ord = max_ord.max(ord);
        if max_ord == i {
            for w in a[start..=i].windows(2) {
                ans = ans.max(w[1].1 - w[0].1);
            }
            start = i + 1;
        }
    }
    writeln!(bw, "{ans}").ok();
}
