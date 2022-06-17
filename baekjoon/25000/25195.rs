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
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        adj[u].push(v);
    }
    let mut fan = vec![false; n];
    let s = sc.next::<usize>();
    for _ in 0..s {
        fan[sc.next::<usize>() - 1] = true;
    }
    let mut check = vec![0; n];
    check[0] = if fan[0] { 2 } else { 1 };
    let mut stack = Vec::with_capacity(n);
    stack.push(0);
    while let Some(u) = stack.pop() {
        for &v in adj[u].iter() {
            let flag = if fan[v] { 2 } else { check[u] };
            if (check[v] ^ flag) != 0 {
                check[v] |= flag;
                stack.push(v);
            }
        }
    }
    let ans = if (0..n).any(|i| adj[i].is_empty() && (check[i] & 1) == 1 && !fan[i]) {
        "yes"
    } else {
        "Yes"
    };
    writeln!(out, "{}", ans).ok();
}
