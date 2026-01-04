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
    let mut a = Vec::with_capacity(1_000);
    let t = sc.read::<usize>();
    for t in 1..=t {
        let n = sc.read::<usize>();
        a.clear();
        a.resize_with(n, || sc.read::<u32>());
        let mut ans = 0;
        while !a.is_empty() {
            let i = a.iter().enumerate().min_by_key(|x| x.1).map(|x| x.0).unwrap();
            ans += i.min(a.len() - 1 - i);
            a.remove(i);
        }
        writeln!(bw, "Case #{t}: {ans}").ok();
    }
}
