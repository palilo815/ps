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
    let k = sc.read::<usize>();
    let mut jews = (0..n).map(|_| (sc.read::<u32>(), sc.read::<u32>())).collect::<Vec<_>>();
    let mut bags = sc.read_vec::<u32>(k);
    jews.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    bags.sort_unstable();
    let mut pq = std::collections::BinaryHeap::new();
    let mut it = jews.into_iter().peekable();
    let mut ans = 0;
    for bag in bags {
        while it.peek().is_some_and(|jew| jew.0 <= bag) {
            pq.push(it.next().unwrap().1);
        }
        ans += pq.pop().unwrap_or_default() as u64;
    }
    writeln!(bw, "{ans}").ok();
}
