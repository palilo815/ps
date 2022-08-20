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
    let m = sc.read::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let s = sc.read_vec::<i32>(n);
    let mut army = s[0];
    let mut check = vec![false; n];
    check[0] = true;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push((0, 0));
    while let Some((enemy, u)) = pq.pop() {
        if -enemy >= army {
            break;
        }
        army -= enemy;
        for &v in adj[u].iter() {
            if !check[v] {
                check[v] = true;
                pq.push((-s[v], v));
            }
        }
    }
    writeln!(out, "{}", army).ok();
}
