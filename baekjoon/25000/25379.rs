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
    let mut even_odd = 0u64;
    let mut odd_even = 0u64;
    let mut even = 0;
    let mut odd = 0;
    for _ in 0..n {
        if sc.read::<u32>() & 1 == 0 {
            even_odd += odd;
            even += 1;
        } else {
            odd_even += even;
            odd += 1;
        }
    }
    writeln!(out, "{}", even_odd.min(odd_even)).ok();
}
