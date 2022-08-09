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
    let xs = (0..n)
        .map(|_| (sc.read::<i32>(), sc.read::<i32>()))
        .collect::<Vec<_>>();
    let m = sc.read::<usize>();
    let ys = (0..m)
        .map(|_| (sc.read::<i32>(), sc.read::<i32>()))
        .collect::<Vec<_>>();
    let a = sc.read::<i32>();
    let b = sc.read::<i32>();
    let (mut l, mut r) = (0, 0);
    let mut sum = 0;
    let mut ans = 0;
    for (i, x) in xs.into_iter() {
        while l != m && ys[l].0 < i + a {
            sum -= ys[l].1 as i64;
            l += 1;
        }
        while r != m && ys[r].0 <= i + b {
            sum += ys[r].1 as i64;
            r += 1;
        }
        ans += sum * x as i64;
    }
    writeln!(out, "{}", ans).ok();
}
