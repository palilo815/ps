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
    let companies = (0..n)
        .map(|_| {
            let m = sc.read::<usize>();
            let max = (0..m).map(|_| sc.read::<usize>()).max().unwrap();
            (m, max)
        })
        .collect::<Vec<_>>();
    let max = companies.iter().map(|x| x.1).max().unwrap();
    let ans = companies.into_iter().map(|(m, pay)| m * (max - pay)).sum::<usize>();
    writeln!(bw, "{ans}").ok();
}
