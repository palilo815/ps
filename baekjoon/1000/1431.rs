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
    let mut a = (0..n).map(|_| sc.read_bytes()).collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| {
        l.len()
            .cmp(&r.len())
            .then({
                let l = l.iter().filter(|c| c.is_ascii_digit()).fold(0, |acc, &x| acc + (x - b'0') as u32);
                let r = r.iter().filter(|c| c.is_ascii_digit()).fold(0, |acc, &x| acc + (x - b'0') as u32);
                l.cmp(&r)
            })
            .then(l.cmp(r))
    });
    for x in a {
        writeln!(bw, "{}", String::from_utf8(x).unwrap()).ok();
    }
}
