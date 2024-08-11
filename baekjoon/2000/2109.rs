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
    a.sort_unstable_by(|l, r| r.1.cmp(&l.1));
    let mut pq = std::collections::BinaryHeap::new();
    let mut it = a.into_iter().peekable();
    let ans = (1..10001).rev().fold(0, |acc, i| {
        while let Some((p, _)) = it.next_if(|x| x.1 == i) {
            pq.push(p);
        }
        acc + pq.pop().unwrap_or_default()
    });
    writeln!(bw, "{ans}").ok();
}

