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
    let mut b = sc.read::<i32>();
    let a = sc.read::<usize>();
    let mut costs = sc.read_vec::<i32>(n);
    costs.sort_unstable();
    for (i, &c) in costs.iter().enumerate().take(a) {
        b -= c / 2;
        if b < 0 {
            writeln!(out, "{}", i).ok();
            return;
        }
    }
    for (i, w) in costs.windows(a + 1).enumerate() {
        b -= w[0] / 2 + w[a] / 2;
        if b < 0 {
            writeln!(out, "{}", a + i).ok();
            return;
        }
    }
    writeln!(out, "{}", n).ok();
}
