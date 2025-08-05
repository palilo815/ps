use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let (mut good, mut bad): (Vec<_>, Vec<_>) =
        (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).partition(|(a, b)| a <= b);
    good.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    bad.sort_unstable_by(|l, r| r.1.cmp(&l.1));
    let (ans, _) = good.into_iter().chain(bad).fold((0, 0), |(ans, capa), (a, b)| {
        if capa < a as i64 {
            (ans + a as i64 - capa, b as i64)
        } else {
            (ans, capa + b as i64 - a as i64)
        }
    });
    writeln!(bw, "{ans}").ok();
}
