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
    let q = sc.read::<usize>();
    let names = (0..n).map(|_| sc.read_array::<20>()).collect::<Vec<_>>();
    let map = names.iter().zip(1..).collect::<std::collections::HashMap<_, _>>();
    for _ in 0..q {
        let q = sc.read_array::<20>();
        if q[0] < b'A' {
            let i = std::str::from_utf8(&q).unwrap().trim_end_matches('\0').parse::<usize>().unwrap() - 1;
            writeln!(bw, "{}", std::str::from_utf8(&names[i]).unwrap().trim_end_matches('\0')).ok();
        } else {
            writeln!(bw, "{}", map.get(&q).unwrap()).ok();
        }
    }
}
