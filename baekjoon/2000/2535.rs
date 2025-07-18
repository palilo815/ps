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
    let mut a = (0..n)
        .map(|_| {
            let country = sc.read::<i32>();
            let man = sc.read::<i32>();
            let score = sc.read::<i32>();
            (country, man, score)
        })
        .collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| r.2.cmp(&l.2));
    let bronze = if a[0].0 == a[1].0 {
        a.iter().position(|&(country, _, _)| country != a[0].0).unwrap()
    } else {
        2
    };
    writeln!(bw, "{} {}", a[0].0, a[0].1).ok();
    writeln!(bw, "{} {}", a[1].0, a[1].1).ok();
    writeln!(bw, "{} {}", a[bronze].0, a[bronze].1).ok();
}
