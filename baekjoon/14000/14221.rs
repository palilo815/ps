use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

#[derive(Eq, PartialEq)]
struct HeapNode(u32, usize);

impl std::cmp::Ord for HeapNode {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0.cmp(&(self.0))
        // self.0.cmp(&(rhs.0))
    }
}

impl std::cmp::PartialOrd for HeapNode {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<u32>();
        adj[u].push((w, v));
        adj[v].push((w, u));
    }
    const INF: u32 = 0x3f3f3f3f;
    let mut dist = vec![INF; n];
    let mut pq = std::collections::BinaryHeap::new();
    let p = sc.next::<usize>();
    let q = sc.next::<usize>();
    let home = (0..p).map(|_| sc.next::<usize>() - 1).collect::<Vec<_>>();
    for _ in 0..q {
        let u = sc.next::<usize>() - 1;
        dist[u] = 0;
        pq.push(HeapNode(0, u));
    }
    while let Some(HeapNode(d, u)) = pq.pop() {
        if d != dist[u] {
            continue;
        }
        for &(w, v) in adj[u].iter() {
            if dist[v] > d + w {
                dist[v] = d + w;
                pq.push(HeapNode(dist[v], v));
            }
        }
    }
    writeln!(
        out,
        "{}",
        home.into_iter().min_by_key(|&i| (dist[i], i)).unwrap() + 1
    )
    .ok();
}
