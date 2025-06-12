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
    let mut count = [0; 14];
    let n = sc.read::<usize>();
    let k = sc.read::<i32>();
    for _ in 0..n {
        let a = sc.read::<usize>();
        let b = sc.read::<usize>() - 1;
        count[6 * a + b] += 1;
    }
    let ans = count.into_iter().map(|c| (c + k - 1) / k).sum::<i32>();
    writeln!(bw, "{ans}").ok();
}
