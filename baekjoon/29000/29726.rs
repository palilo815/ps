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
    let a = sc.read_vec::<i32>(n);
    let ans = a
        .iter()
        .zip(a.iter().skip(n - m - 1))
        .fold((i32::MAX, i32::MIN), |(mn, ans), (&f, &b)| {
            let mn = mn.min(f);
            let ans = ans.max(b - mn);
            (mn, ans)
        })
        .1;
    writeln!(out, "{ans}").ok();
}
