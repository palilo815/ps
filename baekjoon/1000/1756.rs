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
    let d = sc.read::<usize>();
    let n = sc.read::<usize>();
    let mut a = sc.read_vec::<u32>(d);
    for i in 1..a.len() {
        a[i] = a[i].min(a[i - 1]);
    }
    let mut i = a.len();
    for _ in 0..n {
        let x = sc.read::<u32>();
        while i != 0 && a[i - 1] < x {
            i -= 1;
        }
        if i == 0 {
            writeln!(bw, "0").ok();
            return;
        }
        i -= 1;
    }
    writeln!(bw, "{}", i + 1).ok();
}
