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
    let mut a = sc.read_vec::<u32>(n);
    a.sort_unstable();
    let mut ans = Vec::with_capacity(n);
    while !a.is_empty() {
        if *a.first().unwrap() + 1 == *a.last().unwrap() {
            a.reverse();
            ans.append(&mut a);
        } else {
            let i = a.iter().position(|&x| ans.last().is_none_or(|&last| last + 1 != x)).unwrap();
            ans.push(a.remove(i));
        }
    }
    for x in ans {
        write!(bw, "{x} ").ok();
    }
}
