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
    let mut a = (0..n).map(|_| sc.read::<usize>() - 1).collect::<Vec<_>>();
    let mut pos = vec![0; n];
    for (i, &x) in a.iter().enumerate() {
        pos[x] = i;
    }
    let mut dist = vec![0; n];
    for i in 0..n {
        let d = pos[i] - i;
        dist[i] += d;
        dist[a[i]] += d;
        pos[a[i]] = pos[i];
        a[pos[i]] = a[i];
    }
    for x in dist.into_iter() {
        write!(out, "{x} ").ok();
    }
}
