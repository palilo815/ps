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
    let mut a = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| r.0.cmp(&l.0));
    let m = a[0].0;
    let mut it = a.into_iter().peekable();
    let mut pq = std::collections::BinaryHeap::new();
    let mut ans = 0;
    for today in (1..=m).rev() {
        while it.peek().is_some_and(|e| e.0 == today) {
            pq.push(it.next().unwrap().1);
        }
        ans += pq.pop().unwrap_or_default();
    }
    writeln!(bw, "{ans}").ok();
}
