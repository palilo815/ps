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
    let a = sc.next_vec(n);
    let s = sc.next::<usize>() - 1;
    let t = sc.next::<usize>() - 1;
    let mut dist = vec![-1; n];
    let mut q = std::collections::VecDeque::new();
    q.push_back(s);
    while let Some(u) = q.pop_front() {
        for v in (u..n).step_by(a[u]) {
            if dist[v] == -1 {
                dist[v] = dist[u] + 1;
                q.push_back(v);
            }
        }
        for v in (0..=u).rev().step_by(a[u]) {
            if dist[v] == -1 {
                dist[v] = dist[u] + 1;
                q.push_back(v);
            }
        }
    }
    writeln!(out, "{}", dist[t]).ok();
}
