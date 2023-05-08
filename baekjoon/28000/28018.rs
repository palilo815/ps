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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let mut imos = [0; 1_000_002];
    for _ in 0..n {
        imos[sc.read::<usize>()] += 1;
        imos[sc.read::<usize>() + 1] -= 1;
    }
    for i in 0..1_000_000 {
        imos[i + 1] += imos[i];
    }
    let q = sc.read::<usize>();
    for _ in 0..q {
        writeln!(out, "{}", imos[sc.read::<usize>()]).ok();
    }
}
