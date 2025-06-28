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
    const M: usize = 20;
    let n = sc.read::<usize>();
    let mut map = std::collections::HashMap::new();
    for _ in 0..n {
        let e = map.entry(sc.read_array::<M>()).or_insert(0);
        *e += 1;
    }
    let most = *map.values().max().unwrap();
    let (ans, _) = map.into_iter().filter(|e| e.1 == most).max_by(|l, r| l.0.cmp(&r.0)).unwrap();
    let i = ans.iter().position(|&x| x == 0).unwrap_or(M);
    writeln!(bw, "{} {}", String::from_utf8(ans[..i].to_vec()).unwrap(), most).ok();
}
