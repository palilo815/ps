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
    let mut b = vec![0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let k = sc.read::<u32>();
        let a = &mut a[..n];
        a.fill_with(|| sc.read::<u32>());
        let mut parametric = |mut lo, mut hi| {
            let mut f = |mid| -> bool {
                let b = &mut b[..mid];
                b.copy_from_slice(&a[..mid]);
                b.sort_unstable();
                let mut sum = 0;
                for &coin in b.iter() {
                    if sum >= k || coin > sum + 1 {
                        break;
                    }
                    sum += coin;
                }
                sum >= k
            };
            // first true
            while lo != hi {
                let mid = lo + (hi - lo) / 2;
                if f(mid) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }
            lo
        };
        let ans = parametric(1, n + 1);
        writeln!(bw, "{}", if ans == n + 1 { -1 } else { ans as i32 }).ok();
    }
}
