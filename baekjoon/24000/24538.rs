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
    let k = sc.next::<usize>();
    let mut pref_cnt = vec![0; k + 1];
    let mut pref_date = vec![0; k + 1];
    for _ in 0..n {
        let s = sc.next::<usize>() - 1;
        let e = sc.next::<usize>();
        pref_cnt[s] += 1;
        pref_cnt[e] -= 1;
        pref_date[s] += s;
        pref_date[e] -= s;
    }
    for i in 0..k {
        pref_cnt[i + 1] += pref_cnt[i];
        pref_date[i + 1] += pref_date[i];
    }
    for i in 0..k {
        write!(out, "{} ", (i + 1) * pref_cnt[i] - pref_date[i]).ok();
    }
}
