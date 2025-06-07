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
    let s = sc.read::<usize>() - 1;
    let jump = sc.read::<i64>();
    let a = (0..n).map(|_| (sc.read::<i64>(), sc.read::<i64>())).collect::<Vec<_>>();
    let ok = |p1: (i64, i64), p2: (i64, i64)| -> bool {
        let dx = p1.0 - p2.0;
        let dy = p1.1 - p2.1;
        (dx * dx + dy * dy) <= jump * jump
    };
    let mut visited = vec![false; n];
    visited[s] = true;
    let mut stack = Vec::with_capacity(n);
    stack.push(s);
    while let Some(u) = stack.pop() {
        for (v, visited) in visited.iter_mut().enumerate() {
            if !*visited && ok(a[u], a[v]) {
                *visited = true;
                stack.push(v);
            }
        }
    }
    let s = a[s];
    let best = visited
        .into_iter()
        .zip(a)
        .filter_map(|x| if x.0 { Some(x.1) } else { None })
        .max_by_key(|&(x, y)| (s.0 - x) * (s.0 - x) + (s.1 - y) * (s.1 - y))
        .unwrap();
    let (dx, dy) = (s.0 - best.0, s.1 - best.1);
    let ans = ((dx * dx + dy * dy) as f64).sqrt() + jump as f64;
    writeln!(bw, "{:.3}", ans).ok();
}
