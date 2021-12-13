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

use std::io::Write;

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
    let t = sc.next::<usize>();
    for _ in 0..t {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();
        let mut adj = vec![vec![]; n];
        for _ in 0..m {
            let u = sc.next::<usize>() - 1;
            let v = sc.next::<usize>() - 1;
            adj[u].push(v);
            adj[v].push(u);
        }
        let adj = adj;
        let mut stk = Vec::with_capacity(n);
        let mut colour = vec![0_u8; n];
        let mut split = |u| {
            if colour[u] != 0 {
                return true;
            }
            colour[u] = 1;
            stk.push(u);
            while let Some(u) = stk.pop() {
                for &v in &adj[u] {
                    if colour[u] == colour[v] {
                        return false;
                    }
                    if colour[v] == 0 {
                        colour[v] = 3 ^ colour[u];
                        stk.push(v);
                    }
                }
            }
            true
        };
        let ans = (0..n).all(|x| split(x));
        writeln!(out, "{}possible", if ans { "" } else { "im" }).ok();
    }
}
