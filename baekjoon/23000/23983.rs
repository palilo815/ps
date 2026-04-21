use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = Vec::new();
        stdin().lock().read_to_end(&mut buf).ok();
        let s = unsafe { std::str::from_utf8_unchecked(Box::leak(buf.into_boxed_slice())) };
        Self { it: s.split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 7_000;
    const M: usize = 200_000;
    let mut a = [0; N];
    let mut count = vec![0; M + 1];
    let t = sc.read::<usize>();
    for t in 1..=t {
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        a.fill_with(|| sc.read::<usize>());
        a.sort_unstable();
        let zero = a.iter().position(|x| *x != 0).unwrap_or(n);
        let a = &a[zero..];
        let mut ans = zero * (zero - 1) * (zero - 2) / 3 / 2 + zero * (zero - 1) / 2 * (n - zero);
        for (i, x) in a.iter().enumerate().rev() {
            for y in a.iter().take(i).take_while(|&y| x * y <= M) {
                ans += count[x * y];
            }
            count[*x] += 1;
        }
        for x in a {
            count[*x] = 0;
        }
        writeln!(bw, "Case #{t}: {ans}").ok();
    }
}
