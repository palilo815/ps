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
    let mut a = [0; 501];
    for _ in 0..n {
        a[sc.read::<usize>()] = sc.read::<i32>();
    }
    let mut lis = vec![];
    for x in a.into_iter().filter(|&x| x != 0) {
        let lo = lis.partition_point(|&y| y < x);
        if lo == lis.len() {
            lis.push(x);
        } else {
            lis[lo] = x;
        }
    }
    writeln!(bw, "{}", n - lis.len()).ok();
}
