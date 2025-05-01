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
    let q = sc.read::<usize>();
    let a = sc.read_vec::<u32>(n);
    let mut lis = Vec::with_capacity(n);
    let pref = a
        .iter()
        .map(|&x| {
            let i = lis.partition_point(|&y| y < x);
            if i == lis.len() {
                lis.push(x);
            } else {
                lis[i] = x;
            }
            i as u32
        })
        .collect::<Vec<_>>();
    lis.clear();
    let suff = a
        .iter()
        .rev()
        .map(|&x| {
            let i = lis.partition_point(|&y| y > x);
            if i == lis.len() {
                lis.push(x);
            } else {
                lis[i] = x;
            }
            i as u32
        })
        .collect::<Vec<_>>();
    for _ in 0..q {
        let i = sc.read::<usize>() - 1;
        writeln!(bw, "{}", pref[i] + suff[n - 1 - i] + 1).ok();
    }
}
