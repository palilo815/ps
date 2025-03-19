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
    const N: usize = 10;
    let mut a = [0; N];
    let mut b = [0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        let b = &mut b[..n];
        a.fill_with(|| sc.read::<i32>());
        a.iter_mut().for_each(|x| *x += *x & 1);
        let mut ans = 0;
        while a.iter().any(|&x| x != a[0]) {
            ans += 1;
            for i in 0..n {
                b[(i + 1) % n] = a[i] / 2;
            }
            for (a, b) in a.iter_mut().zip(b.iter()) {
                *a = *a / 2 + b;
                *a += *a & 1;
            }
        }
        writeln!(bw, "{ans}").ok();
    }
}
