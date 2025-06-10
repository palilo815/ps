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
    fn next(&mut self) -> Option<&str> {
        self.it.next()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 100_000;
    let mut lis = Vec::with_capacity(N);
    while let Some(n) = sc.next() {
        lis.clear();
        let n = n.parse::<usize>().ok().unwrap();
        for _ in 0..n {
            let x = sc.read::<u32>();
            let i = lis.partition_point(|&y| y < x);
            if i == lis.len() {
                lis.push(x);
            } else {
                lis[i] = x;
            }
        }
        writeln!(bw, "{}", lis.len()).ok();
    }
}
