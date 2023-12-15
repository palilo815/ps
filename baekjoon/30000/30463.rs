use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let k = sc.read::<u32>();
    const M: usize = 1 << 10;
    let mut cnt = [0_i64; M];
    for _ in 0..n {
        cnt[sc.raw().bytes().fold(0, |m, x| m | (1 << (x - b'0')))] += 1;
    }
    let mut ans = 0;
    for (i, &x) in cnt.iter().enumerate() {
        if i.count_ones() == k {
            ans += x * (x - 1) / 2;
        }
        for (j, &y) in cnt.iter().enumerate().take(i) {
            if (i | j).count_ones() == k {
                ans += x * y;
            }
        }
    }
    writeln!(out, "{ans}").ok();
}
