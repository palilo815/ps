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
    let mut pref = vec![0; n + 1];
    for i in 0..n {
        pref[i + 1] = pref[i] + sc.read::<u64>();
    }
    let mut ans = (0, 0);
    let mut map = std::collections::HashMap::new();
    for i in 0..n {
        let x = pref[i + 1] - pref[i];
        let e = map.entry(x).or_insert(pref[i]);
        let s = pref[i + 1] - *e;
        if s > ans.0 {
            ans = (s, 1);
        } else if s == ans.0 {
            ans.1 += 1;
        }
    }
    writeln!(out, "{} {}", ans.0, ans.1).ok();
}
