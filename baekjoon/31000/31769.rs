use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    use std::cmp::Reverse;
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let t = sc.read_vec::<u64>(k);
    let mut pq = t.iter().map(|&t| Reverse(t)).collect::<std::collections::BinaryHeap<_>>();
    let mut edges = (k..n)
        .map(|_| {
            let t1 = pq.pop().unwrap().0;
            let t2 = t1 + sc.read::<u64>();
            pq.push(Reverse(t2));
            (t1, t2)
        })
        .collect::<Vec<_>>();
    edges.sort_unstable_by(|l, r| r.1.cmp(&l.1));
    let bessie = pq.peek().unwrap().0;
    let mut set = std::collections::HashSet::from([bessie]);
    for (u, v) in edges {
        if set.contains(&v) {
            set.insert(u);
        }
    }
    let ans = t.into_iter().map(|t| if set.contains(&t) { b'1' } else { b'0' }).collect::<Vec<_>>();
    writeln!(bw, "{bessie}").ok();
    writeln!(bw, "{}", String::from_utf8(ans).unwrap()).ok();
}
