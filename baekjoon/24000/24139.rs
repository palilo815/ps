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
    let mut p = vec![usize::MAX; n];
    let mut a = vec![0; n];
    _ = sc.read::<usize>();
    a[0] = sc.read::<i32>();
    for i in 1..n {
        p[i] = sc.read::<usize>() - 1;
        a[i] = sc.read::<i32>();
    }
    for i in (1..n).rev() {
        a[p[i]] += 0.max(a[i]);
    }
    writeln!(out, "{}", a.into_iter().max().unwrap()).ok();
}
