use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut a = sc.read_vec::<i32>(n);
    let q = sc.read::<usize>();
    let mut queries = (0..q)
        .map(|i| (sc.read::<usize>() - 1, sc.read::<usize>(), sc.read::<i32>(), i))
        .collect::<Vec<_>>();
    queries.sort_unstable_by(|l, r| l.2.cmp(&r.2).then(l.3.cmp(&r.3)));
    let mut par = (0..n + 1).collect::<Vec<_>>();
    let mut ans = vec![0; q];
    for (l, r, v, qi) in queries {
        let mut i = l;
        loop {
            while par[i] != i {
                par[i] = par[par[i]];
                i = par[i];
            }
            if i >= r {
                break;
            }
            if a[i] > v {
                a[i] = v;
                ans[qi] += 1;
            } else {
                ans[0] += 1;
            }
            par[i] = i + 1;
        }
    }
    ans[0] += par.into_iter().enumerate().take(n).filter(|(i, p)| i == p).count() as i32;
    for i in 1..q {
        ans[i] += ans[i - 1];
    }
    for x in a {
        write!(bw, "{x} ").ok();
    }
    writeln!(bw).ok();
    for x in ans {
        write!(bw, "{x} ").ok();
    }
}
