use std::io::Write;

pub struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    pub fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    pub fn next<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
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

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let s = sc.next::<usize>() - 1;
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    adj.iter_mut()
        .for_each(|x| x.sort_unstable_by(|l, r| r.cmp(l)));
    let mut stk = Vec::with_capacity(n);
    let mut dep = vec![-1; n];
    let mut check = vec![false; n];
    let mut ans = 0;
    let mut t = 0;
    dep[s] = 0;
    stk.push(s);
    while let Some(u) = stk.pop() {
        if !check[u] {
            t += 1;
            ans += dep[u] as usize * t;
            check[u] = true;
        }
        while let Some(v) = adj[u].pop() {
            if dep[v] == -1 {
                dep[v] = dep[u] + 1;
                stk.push(u);
                stk.push(v);
                break;
            }
        }
    }
    writeln!(out, "{}", ans).ok();
}
