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
    const N: usize = 50;
    let mut lis = Vec::with_capacity(N);
    let t = sc.read::<usize>();
    for t in 1..=t {
        lis.clear();
        let n = sc.read::<usize>();
        for _ in 0..n {
            let x = sc.read::<u32>();
            let i = lis.partition_point(|&y| y < x);
            if i == lis.len() {
                lis.push(x);
            } else {
                lis[i] = x;
            }
        }
        writeln!(bw, "Case #{t}: {}", n - lis.len()).ok();
    }
}
