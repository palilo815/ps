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
    let k = sc.next::<usize>();
    const INF: i32 = 0x3f3f3f3f;
    let mut cost = [[INF; 26]; 26];
    for _ in 0..n {
        let uv = sc
            .next_bytes()
            .iter()
            .map(|&x| (x - b'a') as usize)
            .collect::<Vec<_>>();
        cost[uv[0]][uv[1]] = sc.next::<i32>();
    }
    if k == 2 {
        let mut ans = INF;
        for i in 0..26 {
            ans.chmin(cost[i][i]);
        }
        writeln!(out, "{}", if ans == INF { -1 } else { ans }).ok();
        return;
    }
    let m = (k + 1) >> 1;
    let mut dp = vec![[0; 26]; m];
    for i in 1..m {
        dp[i].fill(INF);
        for u in 0..26 {
            if dp[i - 1][u] == INF {
                continue;
            }
            for v in 0..26 {
                if cost[u][v] == INF || cost[v][u] == INF {
                    continue;
                }
                let mut val = dp[i - 1][u] + cost[u][v] + cost[v][u];
                if (k & 1) == 0 && i == m - 1 {
                    val += cost[v][v]
                }
                dp[i][v].chmin(val);
            }
        }
    }
    let ans = *dp.last().unwrap().iter().min().unwrap();
    writeln!(out, "{}", if ans == INF { -1 } else { ans }).ok();
}
