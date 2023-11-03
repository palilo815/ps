use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let h = sc.read_vec::<i32>(n);
    let mut pref = vec![0; n + 1];
    for _ in 0..k {
        let s = sc.read::<usize>();
        let e = sc.read::<usize>() + 1;
        let h = sc.read::<i32>();
        pref[s] += h;
        pref[e] -= h;
    }
    for i in 0..n {
        pref[i + 1] += pref[i];
    }
    for (h, p) in h.into_iter().zip(pref.into_iter()) {
        write!(out, "{} ", h - p).ok();
    }
}
