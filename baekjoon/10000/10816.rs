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
    let mut map = std::collections::HashMap::new();
    for _ in 0..n {
        *map.entry(sc.read::<i32>()).or_insert(0) += 1;
    }
    let m = sc.read::<usize>();
    for _ in 0..m {
        write!(bw, "{} ", map.get(&sc.read::<i32>()).unwrap_or(&0)).ok();
    }
}
