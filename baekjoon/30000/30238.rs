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
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let mut ans = sc.read::<i64>();
        if n != 1 {
            ans += 0.max(sc.read::<i64>());
        }
        ans = 0.max(ans);
        for _ in 2..n {
            ans += 0.max(sc.read::<i64>());
        }
        writeln!(out, "{ans}").ok();
    }
}
