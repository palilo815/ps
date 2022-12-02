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
    let total = a.iter().sum::<i32>() as usize;
    let fence = n - (total - total / n * n);
    if fence != n {
        a.select_nth_unstable(fence);
    }
    let small = (total / n) as i64;
    let moved = a[..fence]
        .iter()
        .fold(0, |acc, &x| acc + (x as i64 - small).abs())
        + a[fence..]
            .iter()
            .fold(0, |acc, &x| acc + (x as i64 - small - 1).abs());
    writeln!(out, "{}", moved / 2).ok();
}
