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

#[derive(Eq, PartialEq)]
struct HeapNode(i32);

impl std::cmp::Ord for HeapNode {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0.abs().cmp(&self.0.abs()).then(rhs.0.cmp(&self.0))
    }
}

impl std::cmp::PartialOrd for HeapNode {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut pq = std::collections::BinaryHeap::new();
    for _ in 0..n {
        match sc.read::<i32>() {
            0 => writeln!(bw, "{}", pq.pop().unwrap_or(HeapNode(0)).0).unwrap(),
            x => pq.push(HeapNode(x)),
        }
    }
}
