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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
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
    let mut s = sc.read_bytes();
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut cur = Vec::with_capacity(n - 1);
    let mut nxt = Vec::with_capacity(n - 1);
    cur.push(0);
    while !cur.is_empty() {
        let last = cur.iter().fold(0, |acc, &x| acc.max(s[x]));
        write!(out, "{}", last as char).ok();
        nxt.clear();
        for &u in cur.iter() {
            if s[u] != last {
                continue;
            }
            s[u] = 0;
            for &v in adj[u].iter().filter(|&&v| s[v] != 0) {
                nxt.push(v);
            }
        }
        std::mem::swap(&mut cur, &mut nxt);
    }
}
