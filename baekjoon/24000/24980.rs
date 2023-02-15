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
    let s = sc.read_bytes();
    let s = (0..n / 2)
        .filter_map(|i| {
            if s[i << 1] == s[i << 1 | 1] {
                None
            } else {
                Some(s[i << 1] == b'G')
            }
        })
        .collect::<Vec<_>>();
    let ans = s.windows(2).filter(|w| w[0] != w[1]).count() + *s.last().unwrap_or(&false) as usize;
    writeln!(out, "{}", ans).ok();
}
