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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let mut x = sc.read::<u64>();
    let n = sc.read::<usize>();
    let mut bits = vec![0; x.count_ones() as usize];
    for b in bits.iter_mut().rev() {
        *b = x & x.wrapping_neg();
        x -= *b;
    }
    while bits.len() > n {
        let x = bits.pop().unwrap();
        *bits.last_mut().unwrap() += x;
    }
    if bits.len() < n {
        writeln!(bw, "-1").ok();
        return;
    }
    x = bits.iter().fold(0, std::ops::BitOr::bitor);
    for b in bits.into_iter() {
        x ^= b;
        write!(bw, "{x} ").ok();
    }
}
