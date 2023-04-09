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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let _ = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<u32>();
    let mut acc = 0;
    for i in 1..=m {
        sc.raw();
        acc += sc.read::<u32>();
        if acc > k {
            writeln!(out, "{i} 1").ok();
            return;
        }
    }
    writeln!(out, "-1").ok();
}
