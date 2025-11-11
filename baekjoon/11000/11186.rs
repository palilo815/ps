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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let k = sc.read::<usize>();
    let s = sc.raw();
    let s = s.bytes().map(|x| (x - b'0') as u32).collect::<Vec<_>>();
    let mut best = (0, k as u32, 0); // ac, len, index
    for len in k..2 * k {
        let mut ac = s.iter().take(len).sum::<u32>();
        if ac * best.1 > best.0 * len as u32 {
            best = (ac, len as u32, 0);
        }
        for i in 0..s.len() - len {
            ac = ac - s[i] + s[i + len];
            if ac * best.1 > best.0 * len as u32 {
                best = (ac, len as u32, i + 1);
            }
        }
    }
    writeln!(bw, "{} {}", best.2 + 1, best.1).ok();
}
