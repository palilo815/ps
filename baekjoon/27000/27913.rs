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
    let q = sc.read::<usize>();
    let mut s = [
        true, false, false, true, false, false, true, false, false, false,
    ]
    .into_iter()
    .cycle()
    .take(n)
    .collect::<Vec<_>>();
    let mut upper = s.iter().filter(|&&x| x).count();
    for _ in 0..q {
        let i = sc.read::<usize>() - 1;
        s[i] ^= true;
        if s[i] {
            upper += 1;
        } else {
            upper -= 1;
        }
        writeln!(out, "{upper}").ok();
    }
}
