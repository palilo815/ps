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
    let t = sc.read::<usize>();
    for _ in 0..t {
        let mut has = [false; 52];
        for _ in 0..26 {
            let x = sc.read_array::<2>();
            let rank = match x[0] {
                b'A' => 12,
                b'K' => 11,
                b'Q' => 10,
                b'J' => 9,
                b'T' => 8,
                _ => (x[0] - b'2') as usize,
            };
            let suit = match x[1] {
                b'D' => 0,
                b'C' => 1,
                b'H' => 2,
                _ => 3,
            };
            let order = rank * 4 + suit;
            has[order] = true;
        }
        let mut gf = 0;
        for x in has {
            if x {
                if gf != 0 {
                    gf -= 1;
                }
            } else {
                gf += 1;
            }
        }
        writeln!(bw, "{}", 26 - gf).ok();
    }
}
