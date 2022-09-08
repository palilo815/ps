use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut adj = vec![vec![]; n + 1];
    for _ in 0..m {
        let u = sc.read::<usize>();
        let v = sc.read::<usize>();
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut prev = vec![0; n + 1];
    prev[1] = usize::MAX;
    let mut deque = std::collections::VecDeque::new();
    deque.push_front(1);
    while let Some(u) = deque.pop_front() {
        for &v in adj[u].iter() {
            if prev[v] == 0 {
                prev[v] = u;
                deque.push_back(v);
            }
        }
    }
    if prev[n] == 0 {
        writeln!(out, "IMPOSSIBLE").ok();
        return;
    }
    let mut path = vec![n];
    let mut u = n;
    while prev[u] != usize::MAX {
        u = prev[u];
        path.push(u);
    }
    writeln!(out, "{}", path.len()).ok();
    for u in path.into_iter().rev() {
        write!(out, "{} ", u).ok();
    }
}
