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
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let mut adj = vec![vec![]; n];
    let mut root = n;
    for i in 0..n {
        let p = sc.next::<usize>();
        if p == 0 {
            root = i;
        } else {
            adj[p - 1].push(i);
        }
    }
    let mut check = vec![false; n];
    for _ in 0..m {
        check[sc.next::<usize>() - 1] = true;
    }
    let mut stk = Vec::with_capacity(n);
    stk.push(root);
    let mut ans = 0;
    while let Some(u) = stk.pop() {
        if check[u] {
            ans += 1;
        } else {
            for &v in adj[u].iter() {
                stk.push(v);
            }
        }
    }
    writeln!(out, "{:?}", ans).ok();
}
