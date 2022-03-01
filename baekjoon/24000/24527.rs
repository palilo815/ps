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
    let h = sc.next::<usize>();
    let left_most = (0..h)
        .scan(1, |state, x| {
            *state += x;
            Some(*state)
        })
        .collect::<Vec<_>>();
    let mut pref = vec![0.0; h + 3];
    let q1 = sc.next::<usize>();
    let q2 = sc.next::<usize>();
    for _ in 0..q1 {
        let a = sc.next::<usize>();
        let b = sc.next::<usize>();
        let dep = left_most.partition_point(|&x| x <= a) - 1;
        let st = a - left_most[dep] + 1;
        let len = h + 1 - dep;
        let b = b as f64 / len as f64;
        pref[st] += b;
        pref[st + len] -= b;
    }
    for i in 0..h + 2 {
        pref[i + 1] += pref[i];
    }
    for i in 0..h + 2 {
        pref[i + 1] += pref[i];
    }
    for _ in 0..q2 {
        let l = sc.next::<usize>() - 1;
        let r = sc.next::<usize>();
        writeln!(out, "{:.6}", pref[r] - pref[l]).ok();
    }
}
