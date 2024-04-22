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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let mut h = vec![0; 200_001];
    let mut ok = vec![false; 200_001];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        for i in 0..n {
            h[i] = sc.read::<usize>();
        }
        h[n] = 0;
        ok[1..=n].fill(false);
        for i in 0..n - 1 {
            if h[i] == h[i + 1] || h[i] == h[i + 2] {
                ok[h[i]] = true;
            }
        }
        for i in (1..=n).filter(|&i| ok[i]) {
            write!(bw, "{i} ").ok();
        }
        if ok.iter().skip(1).take(n).all(|&x| !x) {
            write!(bw, "-1").ok();
        }
        writeln!(bw).ok();
    }
}
