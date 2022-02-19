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
    let mut a = (0..n)
        .map(|_| {
            sc.next::<u32>();
            (sc.next::<u32>(), sc.next::<u32>())
        })
        .collect::<Vec<_>>();
    a.sort_unstable_by(|lhs, rhs| {
        let res = rhs.1.cmp(&lhs.1);
        if res == std::cmp::Ordering::Equal {
            lhs.0.cmp(&rhs.0)
        } else {
            res
        }
    });
    a.dedup();
    let mut dp = Vec::with_capacity(n);
    dp.push(u32::MAX);
    for (x, _) in a {
        if x >= *dp.last().unwrap() {
            dp.push(x);
        } else {
            let i = dp.partition_point(|&elem| elem <= x);
            dp[i] = x;
        }
    }
    writeln!(out, "{}", dp.len()).ok();
}
