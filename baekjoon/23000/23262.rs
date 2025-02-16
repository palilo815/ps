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
    let mut x = vec![0; 200_000];
    let mut y = vec![0; 200_000];
    let t = sc.read::<usize>();
    for tc in 1..=t {
        let k = sc.read::<usize>();
        let x = &mut x[..2 * k];
        let y = &mut y[..2 * k];
        for i in 0..k {
            x[i << 1] = sc.read::<i32>();
            y[i << 1] = sc.read::<i32>();
            x[i << 1 | 1] = sc.read::<i32>();
            y[i << 1 | 1] = sc.read::<i32>();
        }
        x.select_nth_unstable(k - 1);
        y.select_nth_unstable(k - 1);
        writeln!(bw, "Case #{}: {} {}", tc, x[k - 1], y[k - 1]).ok();
    }
}
