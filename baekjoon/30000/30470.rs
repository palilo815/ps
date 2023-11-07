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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let mut a = Vec::with_capacity(n);
    for _ in 0..n {
        if sc.read::<char>() == '1' {
            a.push(sc.read::<i32>());
        } else {
            let m = sc.read::<i32>();
            if let Some(k) = a.last() {
                let x = 0.max(k - m);
                *a.last_mut().unwrap() = x;
            }
        }
    }
    for i in (1..a.len()).rev() {
        a[i - 1] = a[i - 1].min(a[i]);
    }
    writeln!(out, "{}", a.into_iter().fold(0, |acc, x| acc + x as i64)).ok();
}
