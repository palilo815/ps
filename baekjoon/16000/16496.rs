use std::io::Write;

pub struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    pub fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    pub fn next<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    pub fn next_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let mut a = (0..n).map(|_| sc.next_bytes()).collect::<Vec<_>>();
    a.sort_unstable_by(|lhs, rhs| {
        rhs.iter()
            .chain(lhs.iter())
            .cmp(lhs.iter().chain(rhs.iter()))
    });
    if *a[0].first().unwrap() == b'0' {
        write!(out, "0").ok();
    } else {
        for x in a {
            write!(out, "{}", String::from_utf8(x).unwrap()).ok();
        }
    }
}
