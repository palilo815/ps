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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
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
    let s = sc.read_bytes();
    let prev_b = s
        .iter()
        .enumerate()
        .scan(usize::MAX, |p, (i, &x)| {
            if x == b'B' {
                *p = i;
            }
            Some(*p)
        })
        .collect::<Vec<_>>();
    let mut next_r = s
        .iter()
        .enumerate()
        .rev()
        .scan(usize::MAX, |p, (i, &x)| {
            if x == b'R' {
                *p = i;
            }
            Some(*p)
        })
        .collect::<Vec<_>>();
    next_r.reverse();
    for _ in 0..q {
        let l = sc.read::<usize>();
        let r = sc.read::<usize>();
        let a = next_r[l];
        let d = prev_b[r];
        if a == usize::MAX || d == usize::MAX || a == n - 1 || d == 0 {
            writeln!(out, "-1").ok();
            continue;
        }
        let b = next_r[a + 1];
        let c = prev_b[d - 1];
        if b == usize::MAX || c == usize::MAX || b > c {
            writeln!(out, "-1").ok();
        } else {
            writeln!(out, "{a} {b} {c} {d}").ok();
        }
    }
}
