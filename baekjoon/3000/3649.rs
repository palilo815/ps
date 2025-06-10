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
    fn next(&mut self) -> Option<&str> {
        self.it.next()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 1_000_000;
    let mut a = vec![0; N];
    while let Some(w) = sc.next() {
        let w = w.parse::<u32>().unwrap() * 10000000;
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        a.fill_with(|| sc.read::<u32>());
        a.sort_unstable();
        let mut ans = 0;
        let mut j = n - 1;
        for i in 0..n {
            while i < j && a[i] + a[j] > w {
                j -= 1;
            }
            if i == j {
                break;
            }
            if a[i] + a[j] == w {
                ans = a[i];
                break;
            }
        }
        match ans {
            0 => writeln!(bw, "danger").ok().unwrap(),
            x => writeln!(bw, "yes {} {}", x, w - x).ok().unwrap(),
        }
    }
}
