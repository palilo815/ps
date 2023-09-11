use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
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
    let mut c = sc.read_vec::<u64>(n);
    let last = c.pop().unwrap();
    let r1 = c.iter().skip(1).fold((1, 0), |dp, &x| (dp.1 + 1, dp.0.max(dp.1) + x));
    let r2 = c.iter().skip(1).fold((0, c[0]), |dp, &x| (dp.1 + 1, dp.0.max(dp.1) + x));
    let ans = (r1.0.max(r1.1) + last).max((r2.1 + 1).max(r2.0.max(r2.1) + last));
    writeln!(out, "{ans}").ok();
}
