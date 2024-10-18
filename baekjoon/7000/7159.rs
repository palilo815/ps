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
    let _ = sc.read::<usize>();
    let m = sc.read::<usize>();
    let queries = sc.read_vec::<usize>(m);
    let s = sc.read::<usize>();
    for _ in 0..s {
        let mut p = sc.read::<usize>();
        let mut face = true;
        for &query in queries.iter() {
            if p <= query {
                p = query - p + 1;
                face ^= true;
            }
        }
        writeln!(bw, "{}{}", if face { '+' } else { '-' }, p).ok();
    }
}
