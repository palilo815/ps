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
    let mut a = vec![(0, 0); n << 1];
    for i in 0..n {
        a[i << 1] = (sc.read::<u32>(), 1);
        a[i << 1 | 1] = (sc.read::<u32>(), -1);
    }
    a.sort_unstable_by(|lhs, rhs| lhs.0.cmp(&rhs.0));
    let mut ans = 0;
    let mut acc = 0;
    for (_, x) in a.into_iter() {
        acc += x;
        ans = ans.max(acc);
    }
    writeln!(out, "{}", ans).ok();
}
