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
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    if m + k >= n {
        writeln!(out, "100").ok();
        return;
    }
    let mut a = sc.read_vec::<u32>(n);
    a.select_nth_unstable(n - m - k - 1);
    let total = a.iter().fold(0, |acc, &x| acc + x as u64);
    let done = a.into_iter().skip(n - m - k).fold(0, |acc, x| acc + x as u64);
    writeln!(out, "{:.8}", 100.0 * done as f64 / total as f64).ok();
}
