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
    let t = sc.read::<i64>();
    let q = sc.read::<usize>();
    let mut stack = Vec::with_capacity(n);
    let mut loc = vec![0; n];
    let mut meet = i64::MIN;
    for i in 0..n {
        let a = sc.read::<i64>();
        if sc.read::<char>() == '1' {
            loc[i] = a;
            stack.push(i);
        } else {
            if let Some(&j) = stack.last() {
                meet = a - (a - loc[j]) / 2;
            }
            loc[i] = meet.max(a - t);
            while let Some(j) = stack.pop() {
                loc[j] = meet.min(loc[j] + t);
            }
        }
    }
    for i in stack.into_iter() {
        loc[i] += t;
    }
    for _ in 0..q {
        writeln!(out, "{}", loc[sc.read::<usize>() - 1]).ok();
    }
}
