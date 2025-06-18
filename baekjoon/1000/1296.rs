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
    let mut base = [0; 4];
    for c in sc.raw().bytes() {
        match c {
            b'L' => base[0] += 1,
            b'O' => base[1] += 1,
            b'V' => base[2] += 1,
            b'E' => base[3] += 1,
            _ => {}
        }
    }
    let n = sc.read::<usize>();
    let (_, ans) = (0..n)
        .map(|_| {
            let [mut l, mut o, mut v, mut e] = base;
            let s = sc.read::<String>();
            for c in s.bytes() {
                match c {
                    b'L' => l += 1,
                    b'O' => o += 1,
                    b'V' => v += 1,
                    b'E' => e += 1,
                    _ => {}
                }
            }
            (
                100 - ((l + o) * (l + v) * (l + e) * (o + v) * (o + e) * (v + e)) % 100,
                s,
            )
        })
        .min()
        .unwrap();
    writeln!(bw, "{ans}").ok();
}
