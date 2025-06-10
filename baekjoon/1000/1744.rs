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
    let mut a = sc.read_vec::<i32>(n);
    a.retain(|&x| x != 1);
    a.sort_unstable();
    let mut ans = (n - a.len()) as i32;
    let partition = a.iter().position(|x| x.is_positive()).unwrap_or(a.len());
    let (neg, pos) = a.split_at(partition);
    for w in neg.chunks(2) {
        ans += if w.len() == 1 { w[0] } else { w[0] * w[1] };
    }
    for w in pos.rchunks(2) {
        ans += if w.len() == 1 { w[0] } else { w[0] * w[1] };
    }
    writeln!(bw, "{ans}").ok();
}
