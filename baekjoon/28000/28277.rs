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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let q = sc.read::<usize>();
    let mut s = (0..n)
        .map(|_| {
            let m = sc.read::<usize>();
            (0..m).map(|_| sc.read::<u32>()).collect::<std::collections::HashSet<_>>()
        })
        .collect::<Vec<_>>();
    for _ in 0..q {
        match sc.read::<char>() {
            '1' => {
                let u = sc.read::<usize>() - 1;
                let v = sc.read::<usize>() - 1;
                if s[u].len() < s[v].len() {
                    s.swap(u, v);
                }
                let small = std::mem::take(&mut s[v]);
                s[u].extend(small);
            }
            _ => {
                let u = sc.read::<usize>() - 1;
                writeln!(out, "{}", s[u].len()).ok();
            }
        }
    }
}
