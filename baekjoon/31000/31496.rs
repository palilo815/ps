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
    fn read_string(&mut self) -> String {
        self.it.next().unwrap().into()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let s = sc.read_string();
    let mut ans = 0;
    for _ in 0..n {
        let t = sc.read_string();
        let cnt = sc.read::<i32>();
        if t.split('_').any(|w| *w == s) {
            ans += cnt;
        }
    }
    writeln!(out, "{ans}").ok();
}
