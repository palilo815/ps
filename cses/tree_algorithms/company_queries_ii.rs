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
    let q = sc.read::<usize>();
    let mut adj: Vec<Vec<usize>> = vec![vec![]; n];
    let mut p = vec![usize::MAX; n];
    p.iter_mut()
        .skip(1)
        .for_each(|x| *x = sc.read::<usize>() - 1);
    p.iter()
        .enumerate()
        .skip(1)
        .for_each(|(u, &p)| adj[p].push(u));
    let mut stack = Vec::with_capacity(n);
    stack.push(0);
    let topo = (0..n)
        .map(|_| {
            let u = stack.pop().unwrap();
            stack.extend_from_slice(&adj[u]);
            u
        })
        .collect::<Vec<_>>();
    let mut sz = vec![0; n];
    for u in topo.into_iter().rev() {
        sz[u] = adj[u].iter().fold(1, |acc, &v| acc + sz[v]);
        if let Some((heavy, _)) = adj[u]
            .iter()
            .enumerate()
            .max_by(|l, r| sz[*l.1].cmp(&sz[*r.1]))
        {
            let last = adj[u].len() - 1;
            adj[u].swap(heavy, last);
        }
    }
    let mut top = vec![0; n];
    let mut tin = vec![0; n];
    stack.push(0);
    for t in 0..n as u32 {
        let u = stack.pop().unwrap();
        tin[u] = t;
        stack.extend_from_slice(&adj[u]);
        if let Some(heavy) = adj[u].pop() {
            top[heavy] = top[u];
        }
        adj[u].iter().for_each(|&v| top[v] = v);
    }
    for _ in 0..q {
        let mut u = sc.read::<usize>() - 1;
        let mut v = sc.read::<usize>() - 1;
        while top[u] != top[v] {
            if sz[top[u]] < sz[top[v]] {
                u = p[top[u]];
            } else {
                v = p[top[v]];
            }
        }
        writeln!(out, "{}", if tin[u] < tin[v] { u } else { v } + 1).ok();
    }
}
