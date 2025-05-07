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
    let m = sc.read::<u64>();
    let a = sc.read_vec::<u64>(n / 2);
    let b = sc.read_vec::<u64>(n - n / 2);
    let mut a = (0..1 << a.len())
        .map(|bit| {
            a.iter()
                .enumerate()
                .filter_map(|(i, &x)| if bit >> i & 1 == 1 { Some(x) } else { None })
                .sum::<u64>()
        })
        .collect::<Vec<_>>();
    let mut b = (0..1 << b.len())
        .map(|bit| {
            b.iter()
                .enumerate()
                .filter_map(|(i, &x)| if bit >> i & 1 == 1 { Some(x) } else { None })
                .sum::<u64>()
        })
        .collect::<Vec<_>>();
    a.sort_unstable();
    b.sort_unstable();
    let mut ans = 0;
    let mut i = b.len();
    for x in a {
        while i != 0 && x + b[i - 1] > m {
            i -= 1;
        }
        ans += i;
    }
    writeln!(bw, "{ans}").ok();
}
