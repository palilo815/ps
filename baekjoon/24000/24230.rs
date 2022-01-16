use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a String) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let colour = sc.next_vec::<u32>(n);
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut stack = vec![0];
    let mut par = vec![usize::MAX; n];
    while let Some(u) = stack.pop() {
        if let Some(p) = adj[u].iter().position(|&x| x == par[u]) {
            adj[u].swap_remove(p);
        }
        for &v in adj[u].iter() {
            par[v] = u;
            stack.push(v);
        }
    }
    writeln!(
        out,
        "{}",
        (1..n).filter(|&x| colour[x] != colour[par[x]]).count() + (colour[0] != 0) as usize
    )
    .ok();
}
