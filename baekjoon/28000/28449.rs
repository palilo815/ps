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
    let m = sc.read::<usize>();
    let mut team_a = [0; 100_001];
    for _ in 0..n {
        team_a[sc.read::<usize>()] += 1;
    }
    let mut b = sc.read_vec::<usize>(m);
    b.sort_unstable();
    let (mut win, mut draw, mut lose) = (0, 0, 0);
    let mut i = 0;
    let mut acc = 0;
    for b in b.into_iter() {
        while i < b {
            acc += team_a[i];
            i += 1;
        }
        win += acc as usize;
        draw += team_a[b] as usize;
        lose += n - acc as usize - team_a[b] as usize;
    }
    writeln!(out, "{lose} {win} {draw}").ok();
}
