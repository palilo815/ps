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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let l = sc.read::<usize>();
    let mut m = sc.read_vec::<i32>(n);
    m.sort_unstable();
    let mut pref = vec![0; n];
    for _ in 0..k {
        let t = sc.read::<usize>() - 1;
        pref[t] += 1;
        if t + l < n {
            pref[t + l] -= 1;
        }
    }
    for i in 0..n - 1 {
        pref[i + 1] += pref[i];
    }
    pref.sort_unstable();
    let ans = m
        .into_iter()
        .zip(pref.into_iter())
        .take_while(|(_, c)| c < &30)
        .fold(0, |acc, (m, c)| acc + (m >> c) as i64);
    writeln!(out, "{ans}").ok();
}
