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
    let n = sc.read::<u32>();
    let m = sc.read::<u32>();
    let mut v = Vec::with_capacity(n as usize);
    let mut acc = 0;
    let mut large = (u32::MAX, 0);
    for i in 1..=m {
        let x = sc.read::<u32>();
        if x < n {
            v.push(i);
            acc += x;
            if acc >= n {
                break;
            }
        } else {
            large = large.min((x, i));
        }
    }
    if acc < n {
        v = vec![large.1];
    }
    writeln!(out, "{}", v.len()).ok();
    for i in v.into_iter() {
        writeln!(out, "{i}").ok();
    }
}
