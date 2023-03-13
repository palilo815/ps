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
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let a = sc.read_vec::<i64>(n);
    let mut ranges = Vec::with_capacity(n * (n + 1) / 2);
    for i in 0..n {
        ranges.extend(a.iter().enumerate().skip(i).scan(0, |acc, (j, &x)| {
            *acc += x;
            Some((*acc, i, j + 1))
        }));
    }
    ranges.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    let mut ans = vec![i64::MAX; n];
    for (l, r) in ranges.iter().zip(ranges.iter().skip(1)) {
        let diff = r.0 - l.0;
        if l.2 <= r.1 || r.2 <= l.1 {
            for ans in ans.iter_mut().take(l.2).skip(l.1) {
                *ans = diff.min(*ans);
            }
            for ans in ans.iter_mut().take(r.2).skip(r.1) {
                *ans = diff.min(*ans);
            }
        } else {
            for ans in ans.iter_mut().take(l.1.max(r.1)).skip(l.1.min(r.1)) {
                *ans = diff.min(*ans);
            }
            for ans in ans.iter_mut().take(l.2.max(r.2)).skip(l.2.min(r.2)) {
                *ans = diff.min(*ans);
            }
        }
    }
    for x in ans.into_iter() {
        writeln!(out, "{x}").ok();
    }
}
