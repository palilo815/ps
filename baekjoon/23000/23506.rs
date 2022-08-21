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
    let mut xs = vec![0; n];
    let mut ys = vec![0; n];
    for i in 0..n {
        xs[i] = sc.read::<i32>() - 1;
        ys[i] = sc.read::<i32>() - 1;
    }
    xs.sort_unstable();
    ys.sort_unstable();
    let x = xs
        .into_iter()
        .enumerate()
        .fold(0, |acc, (i, x)| acc + (i as i64 - x as i64).abs());
    let y = ys
        .into_iter()
        .enumerate()
        .fold(0, |acc, (i, y)| acc + (i as i64 - y as i64).abs());
    writeln!(out, "{}", x + y).ok();
}
