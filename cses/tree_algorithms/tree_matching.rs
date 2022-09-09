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
    let mut stack = Vec::with_capacity(n - 1);
    stack.push(0);
    let mut topo = vec![0; n];
    for u in topo.iter_mut() {
        *u = stack.pop().unwrap();
        for i in 0..adj[*u].len() {
            let v = adj[*u][i];
            let p = adj[v].iter().position(|x| x == u).unwrap();
            adj[v].swap_remove(p);
            stack.push(v);
        }
    }
    let mut matched = vec![false; n];
    for u in topo.into_iter().rev() {
        if adj[u].iter().any(|&x| !matched[x]) {
            matched[u] = true;
        }
    }
    writeln!(out, "{}", matched.into_iter().filter(|&x| x).count()).ok();
}
