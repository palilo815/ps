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
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let mut p = vec![0.0; 10];
    for p in p.iter_mut() {
        *p = sc.read::<f64>();
    }
    let min_i = p
        .iter()
        .enumerate()
        .min_by(|l, r| l.1.partial_cmp(&r.1).unwrap())
        .unwrap()
        .0;
    p.swap_remove(min_i);
    let r = p.into_iter().fold(1_000_000_000.0, |prod, p| prod * p);
    let d = (1..10).product::<i64>();
    writeln!(out, "{:.7}", r / d as f64).ok();
}
