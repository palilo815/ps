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
    const N: usize = 100_000;
    let mut a = vec![0; N];
    let f = |a: &[i32], b: &[i32]| -> i64 {
        let mut best = 0;
        let mut acc = 0;
        for (&x, &y) in a.iter().rev().zip(b.iter()) {
            acc += (x - y) as i64;
            best = best.max(acc);
        }
        best
    };
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let l = sc.read::<usize>() - 1;
        let r = sc.read::<usize>();
        let a = &mut a[..n];
        a.fill_with(|| sc.read::<i32>());
        let (a, r) = a.split_at_mut(r);
        let (l, a) = a.split_at_mut(l);
        a.sort_unstable();
        l.sort_unstable();
        r.sort_unstable();
        let total = a.iter().fold(0, |acc, &x| acc + x as i64);
        let ans1 = f(a, l);
        let ans2 = f(a, r);
        writeln!(bw, "{}", total - ans1.max(ans2)).ok();
    }
}
