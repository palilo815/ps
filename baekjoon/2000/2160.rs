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
    let n = sc.read::<usize>();
    let a = (0..n)
        .map(|_| {
            std::iter::repeat_with(|| sc.read_bytes())
                .take(5)
                .flatten()
                .fold(0, |mask, x| mask << 1 | (x == b'X') as u64)
        })
        .collect::<Vec<_>>();
    let mut ans = (0, 0);
    let mut best = u32::MAX;
    for i in 0..n {
        for j in i + 1..n {
            let diff = (a[i] ^ a[j]).count_ones();
            if diff < best {
                best = diff;
                ans = (i, j);
            }
        }
    }
    writeln!(bw, "{} {}", ans.0 + 1, ans.1 + 1).ok();
}
