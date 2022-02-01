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
    let mut k = sc.next::<u64>();
    if m < 2 {
        writeln!(out, "YES").ok();
        return;
    }
    let a = sc.next_vec::<u32>(n);
    let mut blocked = vec![false; n];
    for _ in 0..m {
        let mut u = sc.next::<usize>();
        let mut v = sc.next::<usize>();
        if u > v {
            std::mem::swap(&mut u, &mut v);
        }
        blocked[if u == 1 && v == n { 0 } else { u }] = true;
    }
    let ed = blocked.iter().position(|x| *x).unwrap();
    let mut i = ed;
    loop {
        let mut j = if i + 1 == n { 0 } else { i + 1 };
        let mut mn = a[i];
        while j != ed && !blocked[j] {
            mn.chmin(a[j]);
            j = if j + 1 == n { 0 } else { j + 1 };
        }
        let mn = mn as u64;
        if mn > k {
            writeln!(out, "NO").ok();
            return;
        }
        k -= mn;
        if j == ed {
            writeln!(out, "YES").ok();
            return;
        }
        i = j;
    }
}
