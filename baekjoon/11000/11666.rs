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
    let m = sc.read::<i32>();
    let mut schedules = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    schedules.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    let mut pq = std::collections::BinaryHeap::<std::cmp::Reverse<i32>>::with_capacity(n);
    let mut ans = 0;
    for (a, s) in schedules {
        while pq.peek().is_some_and(|x| x.0 + m < a) {
            pq.pop();
        }
        if pq.peek().is_some_and(|x| x.0 <= a) {
            pq.pop();
            ans += 1;
        }
        pq.push(std::cmp::Reverse(a + s));
    }
    writeln!(bw, "{ans}").ok();
}
