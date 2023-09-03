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
    let names = (0..n).map(|_| sc.read_bytes()).collect::<Vec<_>>();
    let test = |s: &[u8], t: &[u8]| -> bool {
        let len = s.len().min(t.len());
        for l in 1..=len {
            if s[..l].eq(&t[t.len() - l..]) {
                return true;
            }
            if t[..l].eq(&s[s.len() - l..]) {
                return true;
            }
        }
        false
    };
    let mut ans = 0;
    for i in 0..n {
        for j in 0..i {
            if test(&names[i], &names[j]) {
                ans += 1;
            }
        }
    }
    writeln!(out, "{ans}").ok();
}
