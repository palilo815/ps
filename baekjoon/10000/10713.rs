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
    let m = sc.read::<usize>();
    let mut pref = vec![0; n];
    let mut prv = sc.read::<usize>() - 1;
    for _ in 1..m {
        let cur = sc.read::<usize>() - 1;
        pref[prv.min(cur)] += 1;
        pref[prv.max(cur)] -= 1;
        prv = cur;
    }
    for i in 1..n {
        pref[i] += pref[i - 1];
    }
    let mut ans = 0;
    for x in pref.into_iter().take(n - 1) {
        let x = x as i64;
        let a = sc.read::<i64>();
        let b = sc.read::<i64>();
        let c = sc.read::<i64>();
        ans += (a * x).min(b * x + c);
    }
    writeln!(out, "{ans}").ok();
}
