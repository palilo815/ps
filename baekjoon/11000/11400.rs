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

trait ChMinMax {
    fn chmin(&mut self, x: Self) -> bool;
    fn chmax(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChMinMax for T {
    fn chmin(&mut self, x: Self) -> bool {
        *self > x && {
            *self = x;
            true
        }
    }
    fn chmax(&mut self, x: Self) -> bool {
        *self < x && {
            *self = x;
            true
        }
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    fn dfs(
        adj: &[Vec<usize>],
        disc: &mut [i32],
        bridges: &mut Vec<(u32, u32)>,
        u: usize,
        p: usize,
    ) -> i32 {
        static mut T: i32 = 0;
        let mut res = unsafe {
            T += 1;
            T
        };
        disc[u] = res;
        for &v in adj[u].iter().filter(|&&v| v != p) {
            if disc[v] == -1 {
                let lo = dfs(adj, disc, bridges, v, u);
                res.chmin(lo);
                if lo > disc[u] {
                    bridges.push((u as u32, v as u32));
                }
            } else {
                res.chmin(disc[v]);
            }
        }
        res
    }
    let mut disc = vec![-1; n];
    let mut bridges = vec![];
    for i in 0..n {
        if disc[i] == -1 {
            dfs(&adj, &mut disc, &mut bridges, i, usize::MAX);
        }
    }
    bridges
        .iter_mut()
        .filter(|(x, y)| *x > *y)
        .for_each(|(x, y)| std::mem::swap(x, y));
    bridges.sort_unstable();
    writeln!(out, "{}", bridges.len()).ok();
    for e in bridges {
        writeln!(out, "{} {}", e.0 + 1, e.1 + 1).ok();
    }
}
