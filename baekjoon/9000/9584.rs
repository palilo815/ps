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
    const M: usize = 9;
    let key = sc.read_array::<M>();
    let n = sc.read::<usize>();
    let ans = (0..n)
        .filter_map(|_| {
            let s = sc.read_array::<M>();
            if key.iter().zip(s.iter()).all(|(k, s)| *k == b'*' || k == s) {
                Some(s)
            } else {
                None
            }
        })
        .collect::<Vec<_>>();
    writeln!(bw, "{}", ans.len()).ok();
    for s in ans {
        writeln!(bw, "{}", String::from_utf8(s.to_vec()).unwrap()).ok();
    }
}
