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
    let mut pq = (0..n)
        .map(|_| std::cmp::Reverse(sc.read::<u32>()))
        .collect::<std::collections::BinaryHeap<_>>();
    let mut ans = 0;
    while pq.len() != 1 {
        let x = pq.pop().unwrap().0;
        ans += pq.peek().unwrap().0 + x;
        pq.peek_mut().unwrap().0 += x;
    }
    writeln!(bw, "{ans}").ok();
}
