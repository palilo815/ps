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
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let a = (0..n).map(|_| sc.read_bytes()).collect::<Vec<_>>();
        let f = || {
            for (i, x) in a.iter().enumerate() {
                for (j, y) in a.iter().enumerate() {
                    if i != j && x.iter().chain(y.iter()).eq(x.iter().chain(y.iter()).rev()) {
                        return x.clone().into_iter().chain(y.clone().into_iter()).collect::<Vec<_>>();
                    }
                }
            }
            vec![b'0']
        };
        writeln!(bw, "{}", String::from_utf8(f()).unwrap()).ok();
    }
}
