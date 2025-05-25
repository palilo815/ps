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
    const N: usize = 1_000;
    let mut a = [0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let mut j = sc.read::<i32>();
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        a.fill_with(|| sc.read::<i32>() * sc.read::<i32>());
        a.sort_unstable();
        let mut ans = 0;
        for &x in a.iter().rev() {
            ans += 1;
            j -= x;
            if j <= 0 {
                break;
            }
        }
        writeln!(bw, "{ans}").ok();
    }
}
