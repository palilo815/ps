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
    let m = sc.read::<u32>();
    let a = sc.read_vec::<u32>(n);
    let mut ans = 0;
    for (i, &x) in a.iter().enumerate() {
        for (j, &y) in a.iter().enumerate().take(i) {
            for &z in a.iter().take(j) {
                let sum = x + y + z;
                if sum <= m {
                    ans = ans.max(sum);
                }
            }
        }
    }
    writeln!(bw, "{ans}").ok();
}
