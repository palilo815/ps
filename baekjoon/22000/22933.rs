use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a String) -> Scanner<'a> {
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

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let k = sc.next::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<i64>();
        adj[u].push((w, v));
    }
    let mut trav = sc.next_vec::<i64>(k);
    trav.sort_unstable();
    const INF: i64 = 0x3f3f3f3f3f3f3f3f;
    let mut dist = vec![INF; n];
    dist[0] = 0;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(std::cmp::Reverse((0, 0)));
    while let Some(std::cmp::Reverse((d, u))) = pq.pop() {
        if d != dist[u] {
            continue;
        }
        for &(w, v) in adj[u].iter() {
            if dist[v] > d + w {
                dist[v] = d + w;
                pq.push(std::cmp::Reverse((dist[v], v)));
            }
        }
    }
    if *dist.last().unwrap() < *trav.last().unwrap() {
        writeln!(out, "0").ok();
        return;
    }
    let mut par = vec![usize::MAX; n];
    let mut dup = vec![false; n];
    pq.push(std::cmp::Reverse((0, 0)));
    while let Some(std::cmp::Reverse((d, u))) = pq.pop() {
        for &(w, v) in adj[u].iter() {
            if d + w != dist[v] {
                continue;
            }
            let upper = trav.partition_point(|&x| x <= d);
            if upper != trav.len() && trav[upper] < d + w {
                continue;
            }
            if par[v] == usize::MAX {
                pq.push(std::cmp::Reverse((d + w, v)));
                par[v] = u;
                dup[v] = dup[u];
            } else {
                dup[v] = true;
            }
        }
    }
    if *par.last().unwrap() == usize::MAX {
        writeln!(out, "0").ok();
        return;
    }
    if *dup.last().unwrap() {
        writeln!(out, "1").ok();
        return;
    }
    let mut path = vec![];
    let mut u = n - 1;
    while u != usize::MAX {
        path.push(u);
        u = par[u];
    }
    writeln!(out, "{}", path.len()).ok();
    for &x in path.iter().rev() {
        writeln!(out, "{}", x + 1).ok();
    }
}
