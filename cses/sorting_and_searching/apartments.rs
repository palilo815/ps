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
    let m = sc.read::<usize>();
    let k = sc.read::<i32>();
    let mut a = sc.read_vec::<i32>(n);
    let mut b = sc.read_vec::<i32>(m);
    a.sort_unstable();
    b.sort_unstable();
    let mut ans = 0;
    let mut i = 0;
    for x in a.into_iter() {
        while i != m && b[i] < x - k {
            i += 1;
        }
        if i != m && b[i] <= x + k {
            ans += 1;
            i += 1;
        }
    }
    writeln!(out, "{}", ans).ok();
}
