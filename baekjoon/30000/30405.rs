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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut cnt = vec![0; m];
    for _ in 0..n {
        let k = sc.read::<usize>();
        cnt[sc.read::<usize>() - 1] += 1;
        for _ in 2..k {
            sc.raw();
        }
        cnt[sc.read::<usize>() - 1] += 1;
    }
    let mut acc = 0;
    for (i, c) in cnt.into_iter().enumerate() {
        acc += c;
        if acc >= n {
            writeln!(out, "{}", i + 1).ok();
            return;
        }
    }
}
