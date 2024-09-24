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
    let mut cnt = [0_u64; 1 << 10];
    for _ in 0..n {
        let mut x = sc.read::<u64>();
        let mask = {
            let mut m = 0;
            while x != 0 {
                m |= 1 << (x % 10);
                x /= 10;
            }
            m
        };
        cnt[mask] += 1;
    }
    let mut ans = 0;
    for (i, &x) in cnt.iter().enumerate() {
        for (j, &y) in cnt.iter().enumerate().take(i) {
            if (i & j) != 0 {
                ans += x * y;
            }
        }
    }
    for x in cnt {
        ans += x * (x - 1) / 2;
    }
    writeln!(bw, "{ans}").ok();
}
