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
    const MOD: u32 = 1_000_000_007;
    let mut prv = vec![(0, 0); m + 1];
    let mut cur = prv.clone();
    let mut ans = 0;
    for _ in 0..n {
        std::mem::swap(&mut cur, &mut prv);
        cur.fill((0, 0));
        for (i, x) in sc.next_bytes().into_iter().enumerate() {
            cur[i + 1].0 = (MOD - prv[i].0 + prv[i + 1].0 + cur[i].0 + (x == b'E') as u32) % MOD;
            cur[i + 1].1 = (MOD - prv[i].1 + prv[i + 1].1 + cur[i].1) % MOD;
            if x == b'S' {
                cur[i + 1].1 += cur[i + 1].0;
                if cur[i + 1].1 >= MOD {
                    cur[i + 1].1 -= MOD;
                }
            } else if x == b'M' {
                ans += cur[i + 1].1;
                if ans >= MOD {
                    ans -= MOD;
                }
            }
        }
    }
    writeln!(out, "{}", ans).ok();
}
