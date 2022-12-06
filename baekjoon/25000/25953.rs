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
    let n = sc.read::<usize>();
    let t = sc.read::<usize>();
    let m = sc.read::<usize>();
    let s = sc.read::<usize>();
    let e = sc.read::<usize>();
    const INF: i32 = 0x3f3f3f3f;
    let mut dp = vec![INF; n];
    let mut tmp = vec![0; n];
    dp[s] = 0;
    for _ in 0..t {
        tmp.copy_from_slice(&dp);
        for _ in 0..m {
            let u = sc.read::<usize>();
            let v = sc.read::<usize>();
            let w = sc.read::<i32>();
            dp[v] = dp[v].min(tmp[u] + w);
            dp[u] = dp[u].min(tmp[v] + w);
        }
    }
    writeln!(out, "{}", if dp[e] == INF { -1 } else { dp[e] }).ok();
}
