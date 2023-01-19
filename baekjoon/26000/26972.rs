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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
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
    let mut h = sc.read_vec::<i64>(n);
    let k = h.iter().sum::<i64>() / n as i64;
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut topo = Vec::with_capacity(n);
    topo.push(0);
    for i in 0..n {
        let u = topo[i];
        for v in adj[u].clone() {
            let p = adj[v].iter().position(|&x| x == u).unwrap();
            adj[v].swap_remove(p);
            topo.push(v);
        }
    }
    let mut do_now = vec![];
    let mut do_later = vec![];
    for u in topo.into_iter().rev() {
        for &v in adj[u].iter() {
            if h[v] > k {
                do_now.push((v + 1, u + 1, h[v] - k));
            } else if h[v] < k {
                do_later.push((u + 1, v + 1, k - h[v]));
            }
            h[u] += h[v] - k;
        }
    }
    writeln!(out, "{}", do_now.len() + do_later.len()).ok();
    for (u, v, w) in do_now.into_iter() {
        writeln!(out, "{u} {v} {w}").ok();
    }
    for (u, v, w) in do_later.into_iter().rev() {
        writeln!(out, "{u} {v} {w}").ok();
    }
}
