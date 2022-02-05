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
struct HeapNode(i32, usize);

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
    let mut doges = vec![std::collections::BTreeSet::new(); n];
    let s = sc.next::<usize>();
    doges[s].insert(sc.next::<usize>());
    let t = sc.next::<usize>();
    doges[t].insert(sc.next::<usize>());
    for _ in 2..m {
        doges[sc.next::<usize>()].insert(sc.next::<usize>());
    }
    const INF: i32 = 0x3f3f3f3f;
    let mut dist = vec![INF; n];
    dist[s] = 0;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(HeapNode(0, s));
    while let Some(HeapNode(d, u)) = pq.pop() {
        if d != dist[u] {
            continue;
        }
        for p in doges[u].iter() {
            for (v, jump) in (u..n).step_by(*p).skip(1).zip(1..) {
                if dist[v] > d + jump {
                    dist[v] = d + jump;
                    pq.push(HeapNode(dist[v], v));
                }
                if doges[v].contains(p) {
                    break;
                }
            }
            for (v, jump) in (0..=u).rev().step_by(*p).skip(1).zip(1..) {
                if dist[v] > d + jump {
                    dist[v] = d + jump;
                    pq.push(HeapNode(dist[v], v));
                }
                if doges[v].contains(p) {
                    break;
                }
            }
        }
    }
    writeln!(out, "{}", if dist[t] == INF { -1 } else { dist[t] }).ok();
}
