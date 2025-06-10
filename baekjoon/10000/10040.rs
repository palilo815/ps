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
    let cost = sc.read_vec::<i32>(n);
    let mut vote = vec![0; n];
    for _ in 0..m {
        let need = sc.read::<i32>();
        let i = cost.iter().position(|&c| c <= need).unwrap();
        vote[i] += 1;
    }
    let (ans, _) = vote.into_iter().enumerate().max_by(|l, r| l.1.cmp(&r.1)).unwrap();
    writeln!(bw, "{}", ans + 1).ok();
}
