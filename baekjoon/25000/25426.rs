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
    let mut ans = 0;
    let mut a = (0..n)
        .map(|_| {
            let a = sc.read::<i32>();
            ans += sc.read::<i64>();
            a
        })
        .collect::<Vec<_>>();
    a.sort_unstable();
    ans = a
        .into_iter()
        .enumerate()
        .fold(ans, |acc, (i, a)| acc + (i + 1) as i64 * a as i64);
    writeln!(out, "{}", ans).ok();
}
