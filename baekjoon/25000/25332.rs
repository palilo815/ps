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
    let a = sc.read_vec::<i32>(n);
    let mut ans = 0;
    let mut delta = 0;
    let mut dp = std::collections::HashMap::new();
    dp.insert(0, 1);
    for a in a.into_iter() {
        let b = sc.read::<i32>();
        delta += b - a;
        if let Some(cnt) = dp.get(&delta) {
            ans += *cnt as i64;
        }
        *dp.entry(delta).or_insert(0) += 1;
    }
    writeln!(out, "{}", ans).ok();
}
