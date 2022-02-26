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
    let mut a = (0..n + 1)
        .map(|i| (sc.next::<i32>(), i))
        .collect::<Vec<_>>();
    let mut b = sc.next_vec::<i32>(n);
    a.sort_unstable_by(|lhs, rhs| lhs.0.cmp(&rhs.0));
    b.sort_unstable();
    let mut pref = vec![0; n + 1];
    for i in 0..n {
        pref[i + 1] = pref[i].max(0.max(a[i].0 - b[i]));
    }
    let mut suff = vec![0; n + 1];
    for i in (0..n).rev() {
        suff[i] = suff[i + 1].max(0.max(a[i + 1].0 - b[i]));
    }
    let mut ans = vec![0; n + 1];
    for i in 0..n + 1 {
        ans[a[i].1] = pref[i].max(suff[i]);
    }
    for x in ans {
        write!(out, "{} ", x).ok();
    }
}
