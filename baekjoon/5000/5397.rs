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
    const N: usize = 1_000_000;
    let mut left = Vec::with_capacity(N);
    let mut right = Vec::with_capacity(N);
    let t = sc.read::<usize>();
    for _ in 0..t {
        left.clear();
        right.clear();
        for c in sc.raw().bytes() {
            match c {
                b'<' => {
                    if let Some(c) = left.pop() {
                        right.push(c);
                    }
                }
                b'>' => {
                    if let Some(c) = right.pop() {
                        left.push(c);
                    }
                }
                b'-' => {
                    left.pop();
                }
                x => left.push(x),
            }
        }
        let ans = left.iter().chain(right.iter().rev()).cloned().collect::<Vec<_>>();
        writeln!(bw, "{}", String::from_utf8(ans).unwrap()).ok();
    }
}
