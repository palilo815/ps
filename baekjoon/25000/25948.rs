use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let m = sc.read::<usize>();
    let n = sc.read::<usize>();
    let mut next = vec![usize::MAX; n];
    for _ in 0..m {
        let u = sc.read::<usize>();
        let v = sc.read::<usize>();
        next[u] = v;
    }
    let mut dp = next
        .iter()
        .map(|&x| (x == usize::MAX) as i32)
        .collect::<Vec<_>>();
    for s in 0..n {
        let mut u = s;
        let mut x = -1;
        while dp[u] == 0 {
            dp[u] = x;
            x -= 1;
            u = next[u];
        }
        if dp[u] < 0 {
            let cycle = dp[u] - x;
            while dp[u] < 0 {
                dp[u] = cycle;
                u = next[u];
            }
            x = -x;
        } else {
            x = dp[u] - x;
        }
        u = s;
        while dp[u] < 0 {
            dp[u] += x;
            u = next[u];
        }
    }
    writeln!(out, "{}", dp.into_iter().max().unwrap_or(0)).ok();
}
