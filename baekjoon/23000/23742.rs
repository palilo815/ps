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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut a = sc.read_vec::<i32>(n);
    a.sort_unstable();
    let mut solos = a.iter().fold(0, |acc, &x| acc + x as i64);
    let mut group = 0;
    let mut ans = solos;
    for (i, x) in (1..).zip(a.into_iter().rev()) {
        group += x as i64;
        solos -= x as i64;
        ans = ans.max(group * i + solos);
    }
    writeln!(bw, "{ans}").ok();
}
