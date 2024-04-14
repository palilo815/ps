use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut map = std::collections::HashMap::new();
    for _ in 0..n {
        let d = sc.read::<i32>() - sc.read::<i32>();
        *map.entry(d).or_insert(0) += sc.read::<i64>();
    }
    writeln!(bw, "{}", map.into_values().max().unwrap()).ok();
}
