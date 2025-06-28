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
    let p = sc.read::<u32>();
    let m = sc.read::<usize>();
    let mut map = (0..n).map(|_| (sc.read_array::<20>(), 0)).collect::<std::collections::HashMap<_, _>>();
    for _ in 0..m {
        let s = sc.read_array::<20>();
        let x = sc.read::<u32>();
        if let Some(v) = map.get_mut(&s) {
            *v += x;
            if *v >= p {
                let i = s.iter().position(|&c| c == 0).unwrap_or(s.len());
                writeln!(bw, "{} wins!", String::from_utf8(s[..i].to_vec()).unwrap()).ok();
                map.remove(&s);
            }
        }
    }
    if map.len() == n {
        writeln!(bw, "No winner!").ok();
    }
}
