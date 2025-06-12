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
    let mut lis = Vec::with_capacity(n);
    for _ in 0..n {
        let x = sc.read::<i32>();
        let i = lis.partition_point(|&o| o < x);
        if i == lis.len() {
            lis.push(x);
        } else {
            lis[i] = x;
        }
    }
    writeln!(bw, "{}", lis.len()).ok();
}
