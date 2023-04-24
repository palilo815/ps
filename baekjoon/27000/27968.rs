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
    let m = sc.read::<usize>();
    let mut pref = vec![0; m + 1];
    for i in 0..m {
        pref[i + 1] = pref[i] + sc.read::<u64>();
    }
    for _ in 0..n {
        let x = sc.read::<u64>();
        let i = pref.partition_point(|&y| y < x);
        if i == m + 1 {
            writeln!(out, "Go away!").ok();
        } else {
            writeln!(out, "{i}").ok();
        }
    }
}
