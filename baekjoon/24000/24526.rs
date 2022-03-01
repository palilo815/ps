use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
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
    let m = sc.next::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let v = sc.next::<usize>() - 1;
        let u = sc.next::<usize>() - 1;
        adj[u].push(v);
    }
    let mut deg = vec![0; n];
    adj.iter()
        .for_each(|vt| vt.iter().for_each(|&x| deg[x] += 1));
    let mut stk = (0..n).filter(|&i| deg[i] == 0).collect::<Vec<_>>();
    while let Some(u) = stk.pop() {
        for &v in adj[u].iter() {
            deg[v] -= 1;
            if deg[v] == 0 {
                stk.push(v);
            }
        }
    }
    writeln!(out, "{}", deg.into_iter().filter(|&x| x == 0).count()).ok();
}
