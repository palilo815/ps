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
    let m = sc.read::<usize>();
    let n = sc.read::<usize>();
    let mut arr = vec![0; m];
    for _ in 0..n {
        let h = sc.read::<usize>();
        let v = sc.read::<usize>();
        let c = sc.read::<usize>() - 1;
        let mx = *arr[c..c + h].iter().max().unwrap();
        arr[c..c + h].fill(mx + v);
    }
    writeln!(bw, "{}", arr.into_iter().max().unwrap()).ok();
}
