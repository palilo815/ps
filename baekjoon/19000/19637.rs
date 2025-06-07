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
    let m = sc.read::<usize>();
    let mut a = (0..n).map(|_| (sc.read_array::<11>(), sc.read::<u32>())).collect::<Vec<_>>();
    a.dedup_by(|l, r| l.1 == r.1);
    for _ in 0..m {
        let x = sc.read::<u32>();
        let i = a.partition_point(|(_, v)| *v < x);
        let s = a[i].0.into_iter().take_while(|&x| x != 0).collect::<Vec<_>>();
        writeln!(bw, "{}", String::from_utf8(s).unwrap()).ok();
    }
}
