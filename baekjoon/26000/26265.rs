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
    let mut a = (0..n).map(|_| (sc.read_array::<20>(), sc.read_array::<20>())).collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| l.0.cmp(&r.0).then(r.1.cmp(&l.1)));
    for (x, y) in a {
        let x = x.split(|&x| x == 0).next().unwrap();
        let y = y.split(|&x| x == 0).next().unwrap();
        writeln!(bw, "{} {}", String::from_utf8_lossy(x), String::from_utf8_lossy(y)).ok();
    }
}
