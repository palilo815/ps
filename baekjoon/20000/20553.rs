use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
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
    let t = sc.read::<i64>() / 2;
    let h = sc.read_vec::<i32>(n);
    let mut ans = 0;
    let mut pref = 0;
    let mut best_edge = 0;
    for i in 1..n.min(t as usize + 1) {
        let w = (h[i] + h[i - 1]) as i64;
        best_edge = best_edge.max(w);
        pref += w;
        ans = ans.max(pref + (t - i as i64) * best_edge);
    }
    writeln!(bw, "{ans}").ok();
}
