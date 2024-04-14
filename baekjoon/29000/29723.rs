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
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut map = (0..n)
        .map(|_| (sc.read_array::<20>(), sc.read::<i32>()))
        .collect::<std::collections::HashMap<_, _>>();
    let sum_k = (0..k).fold(0, |acc, _| acc + map.remove(&sc.read_array::<20>()).unwrap());
    let mut p = map.into_values().collect::<Vec<_>>();
    p.sort_unstable();
    let worst = sum_k + p.iter().take(m - k).sum::<i32>();
    let best = sum_k + p.iter().rev().take(m - k).sum::<i32>();
    writeln!(bw, "{worst} {best}").ok();
}
