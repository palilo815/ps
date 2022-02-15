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
    let s = sc.next::<usize>() - 1;
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    adj.iter_mut().for_each(|x| x.sort_unstable());
    let mut timer = 0;
    let mut tin = vec![0; n];
    let mut stk = Vec::with_capacity(n);
    stk.push((s, usize::MAX));
    while let Some((u, mut i)) = stk.pop() {
        if i == usize::MAX {
            timer += 1;
            tin[u] = timer;
        }
        i += 1;
        while i != adj[u].len() {
            if tin[adj[u][i]] == 0 {
                stk.push((u, i));
                stk.push((adj[u][i], usize::MAX));
                break;
            }
            i += 1;
        }
    }
    for x in tin {
        writeln!(out, "{}", x).ok();
    }
}
