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
    let k = sc.read::<u32>();
    let a = (0..n)
        .map(|_| (sc.read::<u32>(), sc.read::<u32>(), sc.read::<u32>(), sc.read::<u32>()))
        .collect::<Vec<_>>();
    let me = *a.iter().find(|x| x.0 == k).unwrap();
    let cnt = a
        .into_iter()
        .filter(|x| x.1.cmp(&me.1).then(x.2.cmp(&me.2).then(x.3.cmp(&me.3))) == std::cmp::Ordering::Greater)
        .count();
    writeln!(bw, "{}", cnt + 1).ok();
}
