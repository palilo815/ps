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
    fn read_array<const N: usize>(&mut self) -> [u8; N] {
        let s = self.it.next().unwrap();
        let mut a = [0; N];
        a[..s.len()].copy_from_slice(s.as_bytes());
        a
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut map = std::collections::HashMap::new();
    for i in 0..n {
        let s = sc.read_array::<15>();
        map.insert(s, i);
    }
    let a = (0..n).map(|_| *map.get(&sc.read_array::<15>()).unwrap()).collect::<Vec<_>>();
    let score = a
        .iter()
        .enumerate()
        .fold(0, |acc, (i, x)| acc + a.iter().take(i).filter(|&y| y < x).count());
    writeln!(bw, "{}/{}", score, n * (n - 1) / 2).ok();
}
