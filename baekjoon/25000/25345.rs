use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut cnt = [0; 64];
    for _ in 0..n {
        let a = match sc.read_bytes()[0] {
            b'k' => 0,
            b'e' => 1,
            _ => 2,
        };
        let b = match sc.read_bytes()[0] {
            b'a' => 0,
            b'p' => 1,
            _ => 2,
        };
        let c = match sc.read_bytes()[0] {
            b'r' => 0,
            b'b' => 1,
            _ => 2,
        };
        cnt[a << 4 | b << 2 | c] += 1;
        cnt[a << 4 | b << 2 | 3] += 1;
        cnt[a << 4 | 3 << 2 | c] += 1;
        cnt[a << 4 | 3 << 2 | 3] += 1;
        cnt[3 << 4 | b << 2 | c] += 1;
        cnt[3 << 4 | b << 2 | 3] += 1;
        cnt[3 << 4 | 3 << 2 | c] += 1;
        cnt[3 << 4 | 3 << 2 | 3] += 1;
    }
    for _ in 0..m {
        let a = match sc.read_bytes()[0] {
            b'k' => 0,
            b'e' => 1,
            b'm' => 2,
            _ => 3,
        };
        let b = match sc.read_bytes()[0] {
            b'a' => 0,
            b'p' => 1,
            b'o' => 2,
            _ => 3,
        };
        let c = match sc.read_bytes()[0] {
            b'r' => 0,
            b'b' => 1,
            b'g' => 2,
            _ => 3,
        };
        writeln!(out, "{}", cnt[a << 4 | b << 2 | c]).ok();
    }
}
