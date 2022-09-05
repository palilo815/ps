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
    let n = sc.read::<usize>();
    let mut intervals = (0..n)
        .map(|i| (sc.read::<u32>(), sc.read::<u32>(), i))
        .collect::<Vec<_>>();
    intervals.sort_unstable_by(|lhs, rhs| lhs.0.cmp(&rhs.0).then(rhs.1.cmp(&lhs.1)));
    let mut ans = vec![(false, false); n];
    intervals.iter().rev().fold(u32::MAX, |rmin, (_, r, i)| {
        ans[*i].0 = rmin <= *r;
        rmin.min(*r)
    });
    intervals.iter().fold(0, |rmax, (_, r, i)| {
        ans[*i].1 = *r <= rmax;
        rmax.max(*r)
    });
    for (x, _) in ans.iter() {
        write!(out, "{} ", *x as usize).ok();
    }
    writeln!(out).ok();
    for (_, x) in ans.iter() {
        write!(out, "{} ", *x as usize).ok();
    }
}
