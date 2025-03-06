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
    const M: usize = 1_000_000;
    let mut a = vec![0; M];
    loop {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        if n == 0 {
            break;
        }
        let a = &mut a[..n];
        a.fill_with(|| sc.read::<i32>());
        let mut i = 0;
        let mut ans = 0;
        for _ in 0..m {
            let x = sc.read::<i32>();
            while i != n && a[i] < x {
                i += 1;
            }
            if i != n && a[i] == x {
                ans += 1;
                i += 1;
            }
        }
        writeln!(bw, "{ans}").ok();
    }
}
