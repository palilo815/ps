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
    let ori = sc.read::<u32>();
    let mut pq = (1..n).map(|_| sc.read::<u32>()).collect::<std::collections::BinaryHeap<_>>();
    let mut cur = ori;
    while pq.peek_mut().is_some_and(|x| *x >= cur) {
        cur += 1;
        *pq.peek_mut().unwrap() -= 1;
    }
    writeln!(bw, "{}", cur - ori).ok();
}
