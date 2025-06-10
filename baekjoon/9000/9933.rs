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
    fn read_chars(&mut self) -> Vec<char> {
        self.it.next().unwrap().chars().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let a = (0..n).map(|_| sc.read_chars()).collect::<Vec<_>>();
    let key = a
        .iter()
        .find(|&s| {
            let mut t = s.clone();
            t.reverse();
            a.contains(&t)
        })
        .unwrap();
    writeln!(bw, "{} {}", key.len(), key[key.len() / 2]).ok();
}
