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
    let n = sc.read::<usize>();
    let q = sc.read::<usize>();
    let mut pref = vec![[0; 3]; n + 1];
    for i in 0..n {
        pref[i + 1] = pref[i];
        pref[i + 1][sc.read::<usize>() - 1] += 1;
    }
    for _ in 0..q {
        let l = sc.read::<usize>() - 1;
        let r = sc.read::<usize>();
        let x = pref[r][0] - pref[l][0];
        let y = pref[r][1] - pref[l][1];
        let z = pref[r][2] - pref[l][2];
        writeln!(bw, "{x} {y} {z}").ok();
    }
}
