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
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn lis<T: Copy + PartialOrd>(a: &[T]) -> usize {
    let mut dp = Vec::with_capacity(a.len());
    for x in a.iter() {
        let i = dp.partition_point(|item| item < x);
        if i == dp.len() {
            dp.push(*x);
        } else {
            dp[i] = *x;
        }
    }
    dp.len()
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let a = sc.read_vec::<u32>(n);
    writeln!(out, "{}", lis(&a)).ok();
}
