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
    let x = sc.read::<u64>();
    let a = sc.read_vec::<u32>(n);
    let last = *a.last().unwrap();
    let mut kg = 0;
    for a in a.into_iter() {
        kg += sc.read::<u64>();
        if kg < a as u64 {
            writeln!(out, "-1").ok();
            return;
        }
    }
    writeln!(out, "{}", (kg - last as u64) / x).ok();
}
