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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let a = (0..n)
        .map(|_| {
            let s = sc.read_bytes();
            let d = sc.read::<u32>();
            let m = sc.read::<u32>();
            let y = sc.read::<u32>();
            (s, d | m << 5 | y << 9)
        })
        .collect::<Vec<_>>();
    let x = a.iter().max_by(|l, r| l.1.cmp(&r.1)).unwrap().0.clone();
    let y = a.iter().min_by(|l, r| l.1.cmp(&r.1)).unwrap().0.clone();
    writeln!(bw, "{}", String::from_utf8(x).unwrap()).ok();
    writeln!(bw, "{}", String::from_utf8(y).unwrap()).ok();
}
