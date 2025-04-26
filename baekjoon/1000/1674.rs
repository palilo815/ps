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
    fn raw(&mut self) -> Option<&'static str> {
        self.it.next()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let mut query = vec![];
    let mut chocolate = vec![];
    let mut coffee = vec![];
    while let Some(s) = sc.raw() {
        match s {
            "Query" => query.push(sc.read::<f64>()),
            "Chocolate" => chocolate.push((sc.read::<f64>(), sc.read::<f64>())),
            "Coffee" => coffee.push((sc.read::<f64>(), sc.read::<f64>())),
            _ => unreachable!(),
        }
    }
    query.sort_unstable_by(|l, r| l.partial_cmp(r).unwrap());
    for q in query {
        let mut acc = 0.0;
        acc += chocolate
            .iter()
            .filter(|&&(t, _)| t <= q)
            .map(|&(t, n)| 0_f64.max(8.0 * n - (q - t) / 12.0))
            .sum::<f64>();
        acc += coffee
            .iter()
            .filter(|&&(t, _)| t <= q)
            .map(|&(t, n)| 0_f64.max(2.0 * n - (q - t) * (q - t) / 79.0))
            .sum::<f64>();
        acc = acc.max(1.0);
        writeln!(bw, "{} {:.1}", q as i32, acc).ok();
    }
}
