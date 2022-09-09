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
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut stack = Vec::with_capacity(n);
    let mut dist = vec![0; n];
    let mut dfs = |s: usize, dist: &mut [i32]| {
        dist.fill(-1);
        dist[s] = 0;
        stack.push(s);
        while let Some(u) = stack.pop() {
            for &v in adj[u].iter() {
                if dist[v] == -1 {
                    dist[v] = dist[u] + 1;
                    stack.push(v);
                }
            }
        }
        dist.iter()
            .enumerate()
            .max_by(|l, r| l.1.cmp(&r.1))
            .unwrap()
            .0
    };
    let s = dfs(0, &mut dist);
    let d = dfs(s, &mut dist);
    writeln!(out, "{}", dist[d]).ok();
}
