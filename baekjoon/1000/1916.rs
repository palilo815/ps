use std::io::Write;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn next<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<u32>();
        adj[u].push((w, v));
    }
    let s = sc.next::<usize>() - 1;
    let t = sc.next::<usize>() - 1;
    const INF: u32 = 0x3f3f3f3f;
    let mut colour = vec![0; n];
    let mut par = vec![usize::MAX; n];
    let mut dist = vec![INF; n];
    dist[s] = 0;
    let mut dq = std::collections::VecDeque::new();
    dq.push_back(s);
    while let Some(u) = dq.pop_front() {
        colour[u] = 2;
        for &(w, v) in adj[u].iter() {
            if dist[v] > dist[u] + w {
                dist[v] = dist[u] + w;
                par[v] = u;
                if colour[v] == 0 {
                    colour[v] = 1;
                    dq.push_back(v);
                } else if colour[v] == 2 {
                    colour[v] = 1;
                    dq.push_front(v);
                }
            }
        }
    }
    writeln!(out, "{}", dist[t]).ok();
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}
