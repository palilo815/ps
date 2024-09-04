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
    let q = sc.read::<usize>();
    let mut acc = 0;
    for _ in 0..q {
        match sc.read::<char>() {
            '1' => acc += sc.read::<i32>(),
            _ => acc -= sc.read::<i32>(),
        }
        if acc < 0 {
            writeln!(bw, "Adios").ok();
            return;
        }
    }
    writeln!(bw, "See you next month").ok();
}
