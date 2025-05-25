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
    let m = sc.read::<usize>();
    let a = sc.read_vec::<u32>(m);
    let history = a.iter().enumerate().map(|(i, &x)| (x, i)).collect::<std::collections::HashMap<_, _>>();
    let ans = (0..m)
        .filter_map(|i| {
            if Some(&i) == history.get(&a[i]) {
                Some(a[i])
            } else {
                None
            }
        })
        .take(n);
    for x in ans {
        writeln!(bw, "{:0>8}", x).ok();
    }
}
