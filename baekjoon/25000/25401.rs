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
    let n = sc.read();
    let a = sc.read_vec::<i32>(n);
    let mut best = usize::MAX;
    for (i, &x) in (0i32..).zip(a.iter()) {
        best = best.min(a.iter().filter(|&&y| x != y).count());
        for (j, &y) in (0..).zip(a.iter()) {
            if i == j || x.abs_diff(y) % i.abs_diff(j) != 0 {
                continue;
            }
            let d = (x - y) / (i - j);
            best = best.min((0..).zip(a.iter()).filter(|&(k, &z)| x + d * (k - i) != z).count());
        }
    }
    writeln!(out, "{best}").ok();
}
