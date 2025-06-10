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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let t = sc.read::<usize>();
    for _ in 0..t {
        let mut dict = ('a'..='z').collect::<Vec<_>>();
        let n = sc.read::<usize>();
        for _ in 0..n {
            let x = sc.read::<usize>();
            write!(bw, "{}", dict[x]).ok();
            dict[..=x].rotate_right(1);
        }
        writeln!(bw).ok();
    }
}
