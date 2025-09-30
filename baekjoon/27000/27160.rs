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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut cnt = [0; 4];
    for _ in 0..n {
        let c = sc.raw().bytes().next().unwrap();
        let x = sc.read::<u32>();
        match c {
            b'S' => cnt[0] += x,
            b'B' => cnt[1] += x,
            b'L' => cnt[2] += x,
            _ => cnt[3] += x,
        }
    }
    let yes = cnt.contains(&5);
    writeln!(bw, "{}", if yes { "YES" } else { "NO" }).ok();
}
