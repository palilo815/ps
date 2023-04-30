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
    let t = sc.read::<i32>();
    let mut tele = vec![false; n];
    let cities = (0..n)
        .map(|i| {
            tele[i] = sc.read::<char>() == '1';
            (sc.read::<i32>(), sc.read::<i32>())
        })
        .collect::<Vec<_>>();
    let has_tp = tele.iter().any(|&x| x);
    let mut d0 = vec![0; n];
    let mut d1 = vec![0; n];
    let q = sc.read::<usize>();
    for _ in 0..q {
        let u = cities[sc.read::<usize>() - 1];
        let v = cities[sc.read::<usize>() - 1];
        for (d, other) in d0.iter_mut().zip(cities.iter()) {
            *d = (u.0 - other.0).abs() + (u.1 - other.1).abs();
        }
        for (d, other) in d1.iter_mut().zip(cities.iter()) {
            *d = (v.0 - other.0).abs() + (v.1 - other.1).abs();
        }
        let mut best = if has_tp {
            let u = *d0.iter().zip(tele.iter()).filter(|x| *x.1).min_by(|l, r| l.0.cmp(&r.0)).unwrap().0;
            let v = *d1.iter().zip(tele.iter()).filter(|x| *x.1).min_by(|l, r| l.0.cmp(&r.0)).unwrap().0;
            u + v + t
        } else {
            0
        };
        best = best.min(d0.iter().zip(d1.iter()).map(|x| x.0 + x.1).min().unwrap());
        writeln!(out, "{best}").ok();
    }
}
