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
    let mut zero = 0;
    let mut one = 0;
    for _ in 0..n {
        match sc.read::<usize>() {
            0 => zero += 1,
            1 => one += 1,
            _ => {}
        }
    }
    writeln!(out, "{}", zero * one * 2 + (2 * n - 2 * one - zero - 1) * zero / 2).ok();
}
