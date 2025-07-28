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
    const N: usize = 100_000;
    let mut ids = vec![0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let mut map = std::collections::HashMap::new();
        let n = sc.read::<usize>();
        for _ in 0..n {
            let s = sc.read_array::<10>();
            let x = map.entry(s).or_insert(u32::MAX);
            *x = (*x).min(sc.read::<u32>());
        }
        let ids = &mut ids[..map.len()];
        for (id, x) in ids.iter_mut().zip(map.values()) {
            *id = *x;
        }
        ids.sort_unstable();
        for id in ids {
            write!(bw, "{id} ").ok();
        }
        writeln!(bw).ok();
    }
}
