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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let s = sc.read_bytes();
    let mut pref = vec![[0; 26]; s.len() + 1];
    for (i, c) in s.into_iter().enumerate() {
        pref[i + 1] = pref[i];
        pref[i + 1][(c - b'a') as usize] += 1;
    }
    let q = sc.read::<usize>();
    for _ in 0..q {
        let c = sc.read::<char>() as usize - 'a' as usize;
        let l = sc.read::<usize>();
        let r = sc.read::<usize>() + 1;
        writeln!(bw, "{}", pref[r][c] - pref[l][c]).ok();
    }
}
