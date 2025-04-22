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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut a = sc.read_vec::<u64>(n);
    for x in a.iter_mut() {
        let mut num = *x;
        let mut rev = 0;
        while num != 0 {
            rev = 10 * rev + num % 10;
            num /= 10;
        }
        *x = rev;
    }
    a.sort_unstable();
    for x in a {
        writeln!(bw, "{x}").ok();
    }
}

