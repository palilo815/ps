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
    let n = sc.read::<usize>();
    let c = sc.read::<i32>();
    let ans = (0..n)
        .map(|_| {
            let p = sc.read::<i32>();
            let d = sc.read::<i32>();
            let v = sc.read::<i32>();
            p + d + v * c
        })
        .min()
        .unwrap();
    writeln!(bw, "{ans}").ok();
}
