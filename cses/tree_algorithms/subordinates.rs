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
    for i in 1..n {
        adj[sc.read::<usize>() - 1].push(i);
    }
    let mut dp = vec![0; n];
    let mut stack = Vec::with_capacity(n - 1);
    stack.push(0);
    let mut topo = vec![0; n];
    for u in topo.iter_mut() {
        *u = stack.pop().unwrap();
        for &v in adj[*u].iter() {
            stack.push(v);
        }
    }
    for u in topo.into_iter().rev() {
        dp[u] = adj[u].iter().fold(0, |acc, &v| acc + dp[v] + 1);
    }
    for x in dp.into_iter() {
        write!(out, "{} ", x).ok();
    }
}
