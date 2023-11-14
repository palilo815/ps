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
    let a = sc.read_vec::<usize>(n);
    let m = sc.read::<usize>();
    for _ in 0..m {
        let l = sc.read::<usize>();
        let r = sc.read::<usize>() + 1;
        let mut i = l;
        for &x in a.iter() {
            if l <= x && x < r {
                write!(out, "{i} ").ok();
                i += 1;
            } else {
                write!(out, "{x} ").ok();
            }
        }
        writeln!(out).ok();
    }
}
