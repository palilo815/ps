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
    let d = sc.read::<i32>();
    let rita = sc.read::<i32>();
    let theo = sc.read::<i32>();
    let mut acc1 = (4..4 + d - 1).sum::<i32>();
    let mut acc2 = 0;
    for i in 3.. {
        acc1 += i + d;
        acc2 += i;
        if acc1 + acc2 == rita + theo {
            writeln!(bw, "{}", rita - acc1).ok();
            break;
        }
    }
}
