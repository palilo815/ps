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
    loop {
        let t = sc.read::<usize>();
        let n = sc.read::<usize>();
        if t == 0 && n == 0 {
            break;
        }
        let sum = (0..t)
            .map(|_| {
                sc.raw();
                sc.read::<usize>()
            })
            .sum::<usize>();
        writeln!(bw, "{}", 3 * n - sum).ok();
    }
}
