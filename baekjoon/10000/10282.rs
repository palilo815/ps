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
struct HeapElem(u32, usize);

impl std::cmp::Ord for HeapElem {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0.cmp(&(self.0)) // MinHeap
                             // self.0.cmp(&(rhs.0)) // MaxHeap
    }
}

impl std::cmp::PartialOrd for HeapElem {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let t = sc.next::<usize>();
    for _ in 0..t {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();
        let s = sc.next::<usize>() - 1;
        let mut adj = vec![vec![]; n];
        for _ in 0..m {
            let v = sc.next::<usize>() - 1;
            let u = sc.next::<usize>() - 1;
            let w = sc.next::<u32>();
            adj[u].push((w, v));
        }
        const INF: u32 = 0x3f3f3f3f;
        let mut dist = vec![INF; n];
        dist[s] = 0;
        let mut pq = std::collections::BinaryHeap::new();
        pq.push(HeapElem(0, s));
        while let Some(HeapElem(d, u)) = pq.pop() {
            if d != dist[u] {
                continue;
            }
            for &(w, v) in adj[u].iter() {
                let d = d + w;
                if dist[v] > d {
                    dist[v] = d;
                    pq.push(HeapElem(d, v));
                }
            }
        }
        dist.retain(|x| *x != INF);
        write!(out, "{} ", dist.len()).ok();
        writeln!(out, "{}", dist.into_iter().max().unwrap()).ok();
    }
}
