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
    let s = sc.read_bytes();
    let mut pref = vec![0; n + 1];
    for (i, c) in s.into_iter().enumerate() {
        pref[i + 1] = if c == b'+' { 1 } else { -1 };
    }
    for i in 0..n {
        pref[i + 1] += pref[i];
    }
    let mn = *pref.iter().min().unwrap();
    let mx = *pref.iter().max().unwrap();
    let mut prev = vec![usize::MAX; (mx - mn + 1) as usize];
    let mut ans = 0;
    for (i, p) in pref.into_iter().enumerate() {
        let j = (p - mn) as usize;
        if prev[j] == usize::MAX {
            prev[j] = i;
        }
        ans = ans.max(i - prev[j]);
    }
    writeln!(out, "{ans}").ok();
}
