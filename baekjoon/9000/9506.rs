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
    loop {
        let n = sc.read::<i32>();
        if n == -1 {
            break;
        }
        let mut div = (1..=n / 2).filter(|&x| n % x == 0).collect::<Vec<_>>();
        if n == div.iter().sum() {
            write!(bw, "{n} = ").ok();
            let last = div.pop().unwrap();
            for d in div {
                write!(bw, "{d} + ").ok();
            }
            writeln!(bw, "{last}").ok();
        } else {
            writeln!(bw, "{n} is NOT perfect.").ok();
        }
    }
}
