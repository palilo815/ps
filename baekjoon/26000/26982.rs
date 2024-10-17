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
struct HeapNode(u32, u32);

impl std::cmp::Ord for HeapNode {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0.cmp(&(self.0))
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
    let mut cows = (0..n).map(|i| (sc.read::<u32>(), sc.read::<u32>(), i)).collect::<Vec<_>>();
    cows.sort_unstable_by_key(|c| c.0);
    let mut pq: std::collections::BinaryHeap<HeapNode> = std::collections::BinaryHeap::new();
    let mut ans = vec![0; n];
    for (l, r, i) in cows {
        if pq.peek().is_some_and(|x| x.0 < l) {
            let j = pq.peek().unwrap().1;
            ans[i] = j;
            *pq.peek_mut().unwrap() = HeapNode(r, j);
        } else {
            let j = pq.len() as u32 + 1;
            ans[i] = j;
            pq.push(HeapNode(r, j));
        }
    }
    writeln!(bw, "{}", pq.len()).ok();
    for x in ans {
        writeln!(bw, "{x}").ok();
    }
}
