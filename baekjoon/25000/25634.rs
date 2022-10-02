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
    let mut a = sc.read_vec::<i32>(n);
    a.iter_mut().for_each(|x| {
        if sc.read::<char>() == '0' {
            *x *= -1;
        }
    });
    let sum = a.iter().filter(|x| x.is_positive()).sum::<i32>();
    let best = a.iter().skip(1).fold((a[0], a[0]), |(acc, best), x| {
        let acc = if acc > 0 { 0 } else { acc } + *x;
        (acc, acc.min(best))
    });
    writeln!(out, "{}", sum - best.1).ok();
}
