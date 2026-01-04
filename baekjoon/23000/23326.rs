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
    let mut a = sc.read_vec::<u8>(n);
    let mut set = a
        .iter()
        .enumerate()
        .filter_map(|(i, &x)| if x == 1 { Some(i) } else { None })
        .collect::<std::collections::BTreeSet<_>>();
    let mut i = 0;
    for _ in 0..q {
        let op = sc.read::<char>();
        if op == '1' {
            let x = sc.read::<usize>() - 1;
            if a[x] == 0 {
                set.insert(x);
            } else {
                set.remove(&x);
            }
            a[x] ^= 1;
        } else if op == '2' {
            i = (i + sc.read::<usize>()) % n;
        } else if let Some(ans) = set.range(i..n).next() {
            writeln!(bw, "{}", ans - i).ok();
        } else if let Some(ans) = set.range(0..i).next() {
            writeln!(bw, "{}", ans + n - i).ok();
        } else {
            writeln!(bw, "-1").ok();
        }
    }
}
