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
    let a = sc.read::<usize>() - 1;
    let b = sc.read::<usize>();
    let it = (1..).flat_map(|i| std::iter::repeat_n(i, i)).skip(a).take(b - a);
    let ans = it.sum::<usize>();
    writeln!(bw, "{ans}").ok();
}
