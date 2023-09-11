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
    let a = sc.read_vec::<i32>(n);
    if (n != 1 && a[n - 2] == 1) || *a.last().unwrap() > 2 {
        writeln!(out, "-1").ok();
        return;
    }
    let mut edges = Vec::with_capacity(99_999);
    let mut prev = *a.last().unwrap();
    let mut id = 2;
    if prev == 2 {
        edges.push((1, 2));
        id = 3;
    }
    for d in a.into_iter().rev().skip(1) {
        if d < prev {
            writeln!(out, "-1").ok();
            return;
        }
        for i in 0..d {
            edges.push((std::cmp::max(id - prev, id - i - 1), id + i));
        }
        prev = d;
        id += d;
    }
    writeln!(out, "{}", edges.len() + 1).ok();
    for (u, v) in edges.into_iter() {
        writeln!(out, "{u} {v}").ok();
    }
}
