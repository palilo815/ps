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
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut scores = (0..n)
        .map(|_| (sc.read::<u32>(), sc.read::<u32>()))
        .collect::<Vec<_>>();
    scores.select_nth_unstable_by(k - 1, |lhs, rhs| rhs.1.cmp(&lhs.1));
    scores[k..].select_nth_unstable_by(m - 1, |lhs, rhs| rhs.0.cmp(&lhs.0));
    writeln!(
        out,
        "{}",
        scores
            .into_iter()
            .take(m + k)
            .fold(0, |acc, x| acc + x.0 as u64)
    )
    .ok();
}
